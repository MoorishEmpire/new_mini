#include "../../../includes_bonus/minishell_bonus.h"

static char    *check_current_dir(char *cmd)
{
    char    *full_path;

    full_path = ft_strjoin("./", cmd);
    if (!full_path)
        return (NULL);
    if (access(full_path, X_OK) == 0)
        return (full_path);
    free(full_path);
    return (NULL);
}

static char *build_full_path(char *dir, char *cmd)
{
    char    *tmp;
    char    *full_path;

    tmp = ft_strjoin(dir, "/");
    if (!tmp)
        return (NULL);
    full_path = ft_strjoin(tmp, cmd);
    free(tmp);
    return (full_path);
}

static char    *search_for_path(char *cmd, t_env *env)
{
    char    **paths;
    char    *path;
    int     i;
    char    *full_path;

    path = get_env(env, "PATH");
    if (!path)
        return (NULL);

    paths = ft_split(path, ':');
    free(path);
    if (!paths)
        return (NULL);

    i = 0;
    while (paths[i])
    {
        full_path = build_full_path(paths[i], cmd);
        /*if (!full_path)
        {
            free_split(paths);
            return (NULL);
        }*/
        if (access(full_path, X_OK) == 0)
        {
            free_split(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_split(paths);
    return (NULL);
}

char    *get_cmd_path(char *cmd, t_env *env)
{
    char    *path;

    if (!cmd || !*cmd)
        return (NULL);

    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }

    path = search_for_path(cmd, env);
    if (path)
        return (path);
    return (check_current_dir(cmd));
}