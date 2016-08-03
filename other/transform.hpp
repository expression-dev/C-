string Transform (string expr)
{
	if (expr [0] == '|')
		expr [0] = '{';
	for (int i = 1 ; i < (int)expr.size () ; i ++)
	{
		if (expr [i] == '|')
		{
			switch (expr [i - 1])
			{
				case '+': expr [i] = '{'; break;
				case '-': expr [i] = '{'; break;
				case '*': expr [i] = '{'; break;
				case '/': expr [i] = '{'; break;
				case '^': expr [i] = '{'; break;
				case '~': expr [i] = '{'; break;
				case '>': expr [i] = '{'; break;
				case '<': expr [i] = '{'; break;
				case '(': expr [i] = '{'; break;
				case '|': expr [i] = '{'; break;
				default:  expr [i] = '}';
			}
		}
	}
	return expr;
}
