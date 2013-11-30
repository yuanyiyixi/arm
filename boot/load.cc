#define SPACE           0x20
#define tochar(x) ((char) (((x) + SPACE) & 0xff))
#define untochar(x) ((int) (((x) - SPACE) & 0xff))
static char *bin_start_address; 
static char * os_data_addr; 
static int os_data_state; 

void (*os_data_init) (void) ;
void (*os_data_char) (char new_char) ;

void send_nack (int n)
{
	a_b[0] = START_CHAR;
	a_b[1] = tochar (3);
	a_b[2] = tochar (n);
	a_b[3] = NACK_TYPE;
	a_b[4] = '\0';
	a_b[4] = tochar (chk1 (&a_b[1]));
	a_b[5] = his_eol;
	a_b[6] = '\0';
	s1_sendpacket (a_b);
}
static void bin_data_init (void)
{
	os_data_state = 0;
	os_data_addr = bin_start_address;
}
static void bin_data_char (char new_char)
{
	switch (os_data_state) {
	case 0:					/* data */
		*os_data_addr++ = new_char;
		break;
	}
}
static void set_kerm_bin_mode (unsigned int *addr)
{
	bin_start_address = (char *) addr;
	os_data_init = bin_data_init;
	os_data_char = bin_data_char;
}
void k_data_init (void)
{
	k_data_escape = 0;
	os_data_init ();
}
void k_data_save (void)
{
	k_data_escape_saved = k_data_escape;
	os_data_save ();
}
static void os_data_restore (void)
{
	os_data_state = os_data_state_saved;
	os_data_addr = os_data_addr_saved;
}
void k_data_restore (void)
{
	k_data_escape = k_data_escape_saved;
	os_data_restore ();
}
char ktrans (char in)
{
	if ((in & 0x60) == 0x40) {
		return (char) (in & ~0x40);
	} else if ((in & 0x7f) == 0x3f) {
		return (char) (in | 0x40);
	} else
		return in;
}
void k_data_char (char new_char)
{
	if (k_data_escape) {
		/* last char was escape - translate this character */
		os_data_char (ktrans (new_char));
		k_data_escape = 0;
	} else {
		if (new_char == his_quote) {
			/* this char is escape - remember */
			k_data_escape = 1;
		} else {
			/* otherwise send this char as-is */
			os_data_char (new_char);
		}
	}
}
static int k_recv (void)
{
	char new_char;
	char k_state, k_state_saved;
	int sum;
	int done;
	int length;
	int n, last_n;
	int len_lo, len_hi;

	his_eol = END_CHAR;		/* default end of line character */
	his_pad_count = 0;
	his_pad_char = '\0';
	his_quote = K_ESCAPE;

	done = 0;
	k_state = 0;
	k_data_init ();
	k_state_saved = k_state;
	k_data_save ();
	n = 0;				/* just to get rid of a warning */
	last_n = -1;

	while (!done) {
		send_ptr = send_parms;

		for (;;) {
			switch (getc ()) {
			case START_CHAR:	/* start packet */
				goto START;
			case ETX_CHAR:		/* ^C waiting for packet */
				return (0);
			default:
				;
			}
		}
START:
		sum = 0;
		new_char = getc ();
		if ((new_char & 0xE0) == 0)
			goto packet_error;
		sum += new_char & 0xff;
		length = untochar (new_char);
		/* get sequence number */
		new_char = getc ();
		if ((new_char & 0xE0) == 0)
			goto packet_error;
		sum += new_char & 0xff;
		n = untochar (new_char);
		--length;

		if (n == last_n) {
			k_state = k_state_saved;
			k_data_restore ();
		} 
		else {
			last_n = n;
			k_state_saved = k_state;
			k_data_save ();
		}

		/* get packet type */
		new_char = getc ();
		if ((new_char & 0xE0) == 0)
			goto packet_error;
		sum += new_char & 0xff;
		k_state = new_char;
		--length;
		/* check for extended length */
		if (length == -2) {
			new_char = getc ();
			if ((new_char & 0xE0) == 0)
				goto packet_error;
			sum += new_char & 0xff;
			len_hi = untochar (new_char);
			new_char = getc ();
			if ((new_char & 0xE0) == 0)
				goto packet_error;
			sum += new_char & 0xff;
			len_lo = untochar (new_char);
			length = len_hi * 95 + len_lo;
			/* check header checksum */
			new_char = getc ();
			if ((new_char & 0xE0) == 0)
				goto packet_error;
			if (new_char != tochar ((sum + ((sum >> 6) & 0x03)) & 0x3f))
				goto packet_error;
			sum += new_char & 0xff;
		}
		/* bring in rest of packet */
		while (length > 1) {
			new_char = getc ();
			if ((new_char & 0xE0) == 0)
				goto packet_error;
			sum += new_char & 0xff;
			--length;
			if (k_state == DATA_TYPE) {
				/* pass on the data if this is a data packet */
				k_data_char (new_char);
			} else if (k_state == SEND_TYPE) {
				/* save send pack in buffer as is */
				*send_ptr++ = new_char;
				/* if too much data, back off the pointer */
				if (send_ptr >= &send_parms[SEND_DATA_SIZE])
					--send_ptr;
			}
		}
		/* get and validate checksum character */
		new_char = getc ();
		if ((new_char & 0xE0) == 0)
			goto packet_error;
		if (new_char != tochar ((sum + ((sum >> 6) & 0x03)) & 0x3f))
			goto packet_error;
		/* get END_CHAR */
		new_char = getc ();
		if (new_char != END_CHAR) {
		  packet_error:
			/* restore state machines */
			k_state = k_state_saved;
			k_data_restore ();
			/* send a negative acknowledge packet in */
			send_nack (n);
		} else if (k_state == SEND_TYPE) {
			/* crack the protocol parms, build an appropriate ack packet */
			handle_send_packet (n);
		} else {
			/* send simple acknowledge packet in */
			send_ack (n);
			/* quit if end of transmission */
			if (k_state == BREAK_TYPE)
				done = 1;
		}
	}
	return ((ulong) os_data_addr - (ulong) bin_start_address);
}

static unsigned int load_serial_bin (unsigned int  offset)
{
	int size, i;
	char buf[32];

	set_kerm_bin_mode ((usigned int *) offset);
	size = k_recv ();

	for (i=0; i<100; ++i) {
		if (tstc()) {
			(void) getc();
		}
		udelay(1000);
	}

	flush_cache (offset, size);

	printf("## Total Size      = 0x%08x = %d Bytes\n", size, size);
	sprintf(buf, "%X", size);
	setenv("filesize", buf);

	return offset;
}
int loadb(int argc, char *argv[])
{
	unsigned int offset;
	int load_baudrate;
	if (argc > 1)
		offset = atox(argv[1]+2);
		else offset = 0x22000000;
	if (argc > 2)
		load_baudrate = atoi(argv[2]);
		else load_baudrate = 115200;


		printf ("## Ready for binary (kermit) download "
			"to 0x%08lX at %d bps...\n",
			offset,
			load_baudrate);
		addr = load_serial_bin (offset);

		if (addr == ~0) {
			load_addr = 0;
			printf ("## Binary (kermit) download aborted\n");
			rcode = 1;
		} else {
			printf ("## Start Addr      = 0x%08lX\n", addr);
			load_addr = addr;
		}
		return rcode;
}
