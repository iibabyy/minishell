#include "../../includes/minishell.h"

typedef struct s_echo_params
{
    bool is_param;
    bool prm_e;
    bool prm_E;
    bool prm_n;
    char **spilt_data;
} t_echo_params;

int check_flag(char *data, t_echo_params *param)
{
    char ascii[256];
    int i;
    int j;

    ft_bzero(ascii, 256);
    i = 1;
    j = 0;
    while(data[i])
    {
        if (data[i] != 'n' && data[i] != 'e' && data[i] != 'E')
            return (-1);
        ascii[(int)data[i]] = 1;
        ++i;
    }
    if (ascii[(int)'n'] == 1)
        param->prm_n = true;
    if (ascii[(int)'e'] == 1)
        param->prm_e = true;
    if (ascii[(int)'E'] == 1)
        param->prm_E = true;
    if (i > 1)
        param->is_param = true;
    return (0);
}

void set_params(char **data, t_echo_params *echo_param)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(data[i])
    {
        if(data[i][0] == '-')
        {
            if(check_flag(data[i], echo_param) == -1)
                break;
        }
        i++;
    }
    return;
}

void ft_echo(char *data, int fd)
{
    int i;
    t_echo_params *echo_param;


    i = 0;
    if (ft_strchr(data, fd))
    {
        echo_param->spilt_data = ft_split(data, 32);
        if (! echo_param->split_data)
        {
            print_err(NULL, 1, false);
        }
        set_params(echo_param->spilt_data, echo_param);
    }
    if (echo_param->is_param)
        printf("param\n");
    else
        printf("not param\n");
}

int main (void)
{
    ft_echo("-n salut", STDOUT_FILENO);
    return (0);
}