#include "../../includes/minishell.h"

typedef struct s_quotes_params
{
    bool is_open;
    bool is_str;
    bool one_is_open;
    bool two_is_open;
    bool is_param;
    bool start;
} t_echo_params;



bool check_options(char *data)
{
    int i;

    i = 0;
    while (data[i] && data[i] == 32)
       ++i;
    if (data[i] != '-' || data[i] == '\0')
        return (false);
    if (data[i] == '-')
        ++i;
    if (data[i] == 32)
            return (false);
    while (data[i] && data[i] != 32)
    {
        if (data[i] != 'n')
            return (false);
        ++i;
    }
    return (true);
}

void ft_echo(char *data, int fd)
{
    int i;
    int j;
    i = 0;
 
    t_echo_params *params;
    params = ft_calloc (sizeof(params), 1);
    ft_bzero(params, sizeof(params));
    while (data[i] && data[i] == 32)
        ++i;
    
    while (data[i])
    {
        j = 0;
        /*check if str start with " or ' */
        if (data[i] == '"' && params->one_is_open == false)
            params->two_is_open = true;
        else if (data[i] == 39 && params->two_is_open == false) 
             params->one_is_open = true;

        /*close quotes if we have same quotes char*/
        if (params->one_is_open && data[i] == 39)
            params->one_is_open = false;
        else if (params->two_is_open == true && data[i] == '"')
            params->two_is_open = false;
    
        /*check if we open an other quotes in quotes to determine substr*/
        if(params->two_is_open && data[i] == 39)
        {
            ft_putchar_fd(data[i], fd);
            params->is_str = true;
        }
        else if(params->two_is_open && data[i] == 39 && params->is_str == true)
        {
            ft_putchar_fd(data[i], fd);
            params->is_str = false;
        }
        if (data[i] == '-' && data[i + 1] == 'n' && params->is_str == false && params->start == false)
        {
            j = i + i;
            while(data[j] && data[j] != 32)
            {
                if (data[j] != 'n')
                {
                    params->is_param =  false;
                    break;
                }
                j++;
            }
        }
        else
        {
            if (params->is_param == true)
                i = j;
            ft_putchar_fd(data[i], fd);
        }
        i++;
    }
}

int main (int ac, char **av)
{
    if(ac > 1)
    {
        ft_echo(av[1], STDOUT_FILENO);
    }
    return (0);
}