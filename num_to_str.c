#include <stdio.h>
//将数字转成字符串，注意：当浮点数的精度过高的时候，存在转后精度丢失的问题
unsigned char  *num_to_string(
	float      nbr,             //数字类型的数据，可以传入浮点数，也可以传入整数
	unsigned char    nbr_dig,   //转换后，显示的整数位数
	unsigned char    nbr_dp,    //转换后，显示的小数位数， 比如1234.5678， 当nbr_dig = 2, nbr_dp = 2, 那么格式化后为，"34.56"
	unsigned char   lead_zeros, //该值如果为1， 转换后，如果指定的整数位数，或者小数位数，比实际的要多，那么多出的部分需要补0，反之不需要补0
	unsigned char   nul,        //该值如果为非0， 则表示，转换后，的字符串最后再加上\0，作为字符串的结束
	unsigned char     *pstr_fmt)//输出的字符串
{
	unsigned char    *pstr;
	unsigned char   i;
	unsigned  int   dig_nbr;
	unsigned  int   dig_val;
	float     dig_exp;
	float     dp_exp;

	/* Rtn NULL if str ptr NULL (see Note #6a). */
	if (pstr_fmt == (unsigned char *)0)
	{
		return ((unsigned char *)0);
	}


	pstr = pstr_fmt;

	if (nbr < 0.0)                                              /* If nbr neg,             ...                          */
	{
		if ((nbr_dig > 0) ||                                    /* ... &  at least one dig ...                          */
			(nbr_dp > 0))                                       /* ... or at least one dp; ...                          */
		{
			nbr = -nbr;                                         /* ... negate nbr &        ...                          */
			*pstr++ = '-';                                      /* ... prefix with neg sign (see Note #2b).             */
		}
	}

	if (nbr_dig > 0)
	{
		dig_exp = 1.0;
		for (i = 1; i < nbr_dig; i++)
		{
			dig_exp *= 10.0;
		}
		for (i = nbr_dig; i > 0; i--)                           /* Fmt str for desired nbr digs.                        */
		{
			dig_nbr = (unsigned  int)(nbr / dig_exp);
			if ((dig_nbr > 0) ||                                /* If dig nbr > 0,                              ...     */
				(nbr_dig == 1) ||                               /* ... OR exactly 1 dig to fmt,                 ...     */
				(i == 1) ||                                     /* ... OR on one's  dig to fmt,                 ...     */
				(lead_zeros == 1))                              /* ... OR lead zeros opt ENABLED (see Note #3), ...     */
			{
				/* ... calc & fmt dig val.*/
				dig_val = (unsigned  int)(dig_nbr % 10);
				*pstr++ = (unsigned char)(dig_val + '0');
			}
			dig_exp /= 10.0;                                    /* Shift to next least-significant dig.                 */
		}
	}

	if (nbr_dp > 0)
	{
		*pstr++ = '.';                                          /* Append dp prior to dp conversion.                    */
		dp_exp = 10.0;
		for (i = 0; i < nbr_dp; i++)                            /* Fmt str for desired nbr dp.                          */
		{
			dig_nbr = (unsigned  int)(nbr * dp_exp);
			dig_val = (unsigned  int)(dig_nbr % 10);
			*pstr++ = (unsigned char)(dig_val + '0');
			dp_exp *= 10.0;                                    /* Shift to next least-significant dp.                  */
		}
	}

	if (nul != 0)                                              /* If NOT DISABLED, append NULL char (see Note #4).     */
	{
		*pstr = (unsigned char)0;
	}

	return (pstr_fmt);
}
unsigned char buf[20] = { 0 };
int main(int argc, char *argv[])
{
	/*测试环境：vs2017*/
	num_to_string(1234.5678, 2, 2, 1, 1, buf);
	printf("buf = %s\r\n", buf);  //打印结果：34.56

	num_to_string(1234.5678, 5, 5, 0, 1, buf);
	printf("buf = %s\r\n", buf);  //打印结果：1234.56776

	num_to_string(1234.5678, 5, 5, 1, 1, buf);
	printf("buf = %s\r\n", buf);  //打印结果：01234.56776

	num_to_string(1234.5678, 6, 6, 1, 1, buf);
	printf("buf = %s\r\n", buf);  //打印结果：001234.567768

	num_to_string(1234.5678, 7, 7, 1, 1, buf);
	printf("buf = %s\r\n", buf);  //打印结果：0001234.5677682
	getchar();
}
