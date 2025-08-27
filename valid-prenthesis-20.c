bool isValid(char *s)
{
    char *stack = NULL;
    int top = 0;
    int size = 0;

    while (*s)
    {
        if (*s == '(' || *s == '{' || *s == '[')
        {
            if (top >= size)
            {
                size = size ? size + 1 : 1;
                stack = realloc(stack, size * sizeof(char));
                if (!stack)
                {
                    free(stack);
                    return false;
                }
            }
            stack[top++] = *s;
        }
        else
        {
            if (top == 0)
            {
                free(stack);
                return false;
            }
            if ((*s == ')') && (stack[top - 1] == '('))
            {
                top--;
            }
            else if (*s == '}' && stack[top - 1] == '{')
            {
                top--;
            }
            else if (*s == ']' && stack[top - 1] == '[')
            {
                top--;
            }
            else
            {
                free(stack);
                return false;
            }
        }
        s++;
    }
    bool valid = (top == 0);
    free(stack);
    return valid;
}