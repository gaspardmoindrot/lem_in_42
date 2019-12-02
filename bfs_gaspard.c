#include "lem_in.h"

static void		ft_add_path_history(t_node **son, t_node **father)
{
	t_list *link;

	if (father != NULL && son != NULL)
	{
		link = ft_lstnew_revisited(*father, sizeof(*father));
		ft_lstadd(&((*son)->father), link);
	}
}

static void		ft_stack_virgin_neighbours(t_node **queue, int *i, int *j)
{
	t_list	*tmp;
	t_node	*node;

	tmp = queue[*i]->next;
	*j = (*i != 0) ? *j - 1 : *j;
	while (tmp)
	{
		node = (t_node *)tmp->content;
		if (((node->passed_flag == 0 && (queue[*i]->chance_one != 1 || queue[*i]->passed_flag == 1))
					|| (node->passed_flag == 5 && (queue[*i]->chance_one == 0
						|| (queue[*i]->passed_flag == -5 && tmp->arcw == -1)) && queue[*i]->is_start == 0))
			&& tmp->arcw <= 0 && !(node->is_end == 1 && queue[*i]->passed_flag == -5))
		{
			if (node->passed_flag == 5 && queue[*i]->chance_one == 0)
			{
				node->chance_one = 1;
				node->passed_flag = -5;
			}
			else if (node->passed_flag == 5)
			{
				node->chance_one = 2;
				node->passed_flag = -5;
			}
			else if (node->passed_flag == 0)
			{
				node->chance_one = queue[*i]->chance_one;
				node->passed_flag = 1;
			}
			queue[*i + *j] = node;
			ft_add_path_history(&(queue[*i + *j]), &(queue[*i]));
			(*j)++;
		}
		tmp = tmp->next;
	}
}

int			ft_bfs_gaspard(t_list **list, t_params **params, t_node *start)
{
	t_node		**queue;
	int		i;
	int		j;

	i = 0;
	(void)list;
	queue = (t_node **)malloc(sizeof(t_node *) * (*params)->rooms_count);
	if (!queue)
		return (-1);
	ft_init_queue(queue, (*params)->rooms_count);
	queue[0] = start;
	queue[0]->passed_flag = 1;
	j = 1;
	while (queue[i] && queue[i] != NULL)
	{
		if (queue[i]->is_end == 1)
		{
			ft_put_arcw(queue[i], list);
			free(queue);
			return (1);
		}
		ft_stack_virgin_neighbours(queue, &i, &j);
		i++;
	}
	free(queue);
	return (-1);
}
