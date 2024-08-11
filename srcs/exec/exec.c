#include "../../includes/minishell.h"
#include "exec.h"
#include "../../includes/minishell.h"
#include "exec.h"
#include <unistd.h>

void reset_std(int std)
{
    dup2(std, std);
    fprintf(stderr, "reset std : %d\n", std);
}

void exec_node(t_command *node, t_exec_data *data, int lr_flag)
{
    fprintf(stderr, "Exec_node: Commande '%s', LR_FLAG = %d\n", node->command[0], lr_flag);
    fprintf(stderr, "valeur de fd[0] :%d et fd[1] %d\n", data->fd[0], data->fd[1]);
    if (lr_flag == CMD_LEFT)
    {
        fprintf(stderr, "Exec_node: CMD_LEFT, fermeture fd[0] et redirection de stdout\n");
        if (data->prev_fd[0] != -1) // Si un previous pipe existe
        {
            ft_close(&data->prev_fd[1]);
            fprintf(stderr, "Exec_node: CMD_LEFT, redirection de l'input depuis le previous pipe\n");
            ft_dup2(&data->prev_fd[0], STDIN_FILENO); // Récupère l'input du précédent pipe
            ft_close(&data->prev_fd[0]);
        }
        ft_dup2(&data->fd[1], STDOUT_FILENO);
        ft_close(&data->fd[1]);  // Fermer immédiatement après duplication
        ft_close(&data->fd[0]);
    }
    else if (lr_flag == CMD_RIGHT)
    {
        fprintf(stderr, "Exec_node: CMD_RIGHT, fermeture fd[1] et redirection de stdin\n");
        ft_dup2(&data->fd[0], STDIN_FILENO);
        ft_close(&data->fd[0]);  // Fermer immédiatement après duplication
        ft_close(&data->fd[1]);
        reset_std(STDOUT_FILENO);
    }
    else if (lr_flag == 5)
    {
        fprintf(stderr, "Exec_node: CMD_INTERMEDIATE, redirection de stdin et stdout\n");
        ft_dup2(&data->fd[0], STDIN_FILENO);
        ft_dup2(&data->fd[1], STDOUT_FILENO);
        ft_close(&data->fd[0]);  // Fermer immédiatement après duplication
        ft_close(&data->fd[1]);  // Fermer immédiatement après duplication
    }

    fprintf(stderr, "Exec_node: Exécution de la commande %s\n", data->command_path);
    execve(data->command_path, node->command, NULL);

    // En cas d'erreur d'exécution
    perror("execve");
    exit(EXIT_FAILURE);
}

void execute_lr_command(t_command *left_node, t_command *right_node, t_exec_data *data, bool end)
{
    int status;
    bool right = true;


    init_data(data, right_node);
    if (right_node->command == NULL)
        right = false;
    fprintf(stderr, "execute_lr_command: Création d'un pipe\n");

    if (pipe(data->fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "execute_lr_command: Fork pour le processus de gauche\n");
    data->pid_l = fork();
    if (data->pid_l == 0)
    {
        init_data(data, left_node);
        exec_node(left_node, data, CMD_LEFT);
    }
    else
    {
        fprintf(stderr, "execute_lr_command: Fork pour le processus de droite\n");
        if(right)
        {
            data->pid_r = fork();
            if (data->pid_r == 0)
            {
                if (!end)
                    exec_node(right_node, data, 5);
                else
                    exec_node(right_node, data, CMD_RIGHT);
            }
            else
            {
                fprintf(stderr, "execute_lr_command: Fermeture des pipes dans le processus parent\n");

                // Dans le processus parent, ferme les descripteurs immédiatement après fork
                ft_close(&data->fd[0]);
                ft_close(&data->fd[1]);
            
                waitpid(data->pid_l, &status, 0);
                waitpid(data->pid_r, &status, 0);

                // Mise à jour du previous pipe pour le prochain node
                data->prev_fd[0] = data->fd[0];
                data->prev_fd[1] = data->fd[1];
            }
        }
        else
        {
                ft_close(&data->fd[0]);
                ft_close(&data->fd[1]);
            
                waitpid(data->pid_l, &status, 0);
                if (right)
                    waitpid(data->pid_r, &status, 0);

                // Mise à jour du previous pipe pour le prochain node
                data->prev_fd[0] = data->fd[0];
                data->prev_fd[1] = data->fd[1];
        }
    }
}

pid_t exec_command(t_command *node, t_exec_data *data, bool pipeline)
{
    if (node == NULL)
    {
        fprintf(stderr, "exec_command: Node est NULL, retour 0\n");
        return (0);
    }

    if (node->type == COMMAND)
    {
        fprintf(stderr, "exec_command: Exécution d'une commande simple: %s\n", node->command[0]);
        exec_single_command(node);
    }
    
    if (node->type == PIPE)
    {
        fprintf(stderr, "exec_command: Détection d'un pipe\n");
        if(node->previous && node->previous->type == PIPE)
            execute_lr_command(node->left, node->right, data, pipeline);
        else
            execute_lr_command(node->left, node->right, data, true);
        exec_command(node->previous, data, true); // Passer true pour signifier un pipeline
    }

    return (0);
}
