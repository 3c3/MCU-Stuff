/*
 * ToString.h
 *
 * Created: 26.7.2016 г. 18:15:15
 *  Author: Kosyo
 */ 


#ifndef TOSTRING_H_
#define TOSTRING_H_

int ToString(char* buff, long val)
{
	int idx = 0;
	do
	{
		buff[idx++] = val%10 + '0';
		val/=10;
	} while(val);

	int lim = idx/2;
	char tmp;
	for(int i = 0; i < lim; i++)
	{
		tmp = buff[i];
		buff[i] = buff[idx-i-1];
		buff[idx-i-1] = tmp;
	}

	return idx;
}

#endif /* TOSTRING_H_ */