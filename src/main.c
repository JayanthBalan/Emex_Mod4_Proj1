
#include "apc.h"

int main(int argc, char *argv[])
{
	if(argc != 4) {
		fprintf(stdout, "%s>>> Example Command: ./apc 324 + -1234\n", __FILE__);
		return fail;
	}

	Dlist_t ip_1 = {0}, ip_2 = {0}, op = {0};
	ret_types_e retno;

	retno = convertStrDll(argv[1], &ip_1);
	if(retno == fail) {
		return fail;
	}
	retno = convertStrDll(argv[3], &ip_2);
	if(retno == fail) {
		return fail;
	}

	char operator = *argv[2];

	switch (operator) {
		case '+':
			retno = addition(&ip_1, &ip_2, &op);
			if(retno == pass) {
				display_dll(op);
			}
			break;
		case '-':
			retno = subtraction(&ip_1, &ip_2, &op);
			if(retno == pass) {
				display_dll(op);
			}
			break;
		case 'x':
			retno = multiplication(&ip_1, &ip_2, &op);
			if(retno == pass) {
				display_dll(op);
			}
			break;
		case '/':
			retno = division(&ip_1, &ip_2, &op);
			if(retno == pass) {
				display_dll(op);
			}
			break;
		default:
			fprintf(stderr, "%s>>> Unsupported Operation\n", __FILE__);
	}

	freeAllNodes(&ip_1);
	freeAllNodes(&ip_2);
	freeAllNodes(&op);

	if(retno == fail) {
		fprintf(stderr, "%s>>> Command Failed\n", __FILE__);
	}

	return retno;
}
