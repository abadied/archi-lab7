int dignum(char* str) {
	int counter = 0;
	while(*str != 0) {
		if ((*str >= '0') && (*str <= '9'))
			counter++;
		str++;
	}
	return counter;
}