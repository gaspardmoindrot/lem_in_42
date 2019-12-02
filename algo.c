#include "lem_in.h"

void		ft_put_arcw(t_node *end, t_list **list)
{
	t_list	*tmp;
	t_node	*node;
	t_node	*start;

	tmp = end->father;
	end->passed_flag = 2;
	while (tmp)
	{
		node = (t_node *)tmp->content;
		node->passed_flag = 2;
		tmp = node->father;
	}
	start = ft_find_t_node_with_start(list);
	tmp = start->next;
	start->passed_flag = 3;
	while (tmp)
	{
		node = (t_node *)tmp->content;
		if (node->passed_flag == 2 && tmp->arcw <= 0)
		{
			node->passed_flag = 3;
			if (tmp->arcw == -1)
				tmp->arcw = 0;
			else
				tmp->arcw = 1;
			tmp = node->next;
		}
		else
			tmp = tmp->next;
	}
	tmp = end->next;
	end->passed_flag = 0;
	while (tmp)
	{
		node = (t_node *)tmp->content;
                if (node->passed_flag == 3 && tmp->arcw >= 0)
                {
                        node->passed_flag = 0;
                        if (tmp->arcw == 1)
			{
                                tmp->arcw = 0;
				ft_test_voisin(node);
			}
                        else
			{
                                tmp->arcw = -1;
				node->passed_flag = 5;
			}
                        tmp = node->next;
                }
                else
                        tmp = tmp->next;
	}
}

void	ft_test_voisin(t_node *node)
{
	t_list	*tmp;
	int	count;

	count = 0;
	tmp = node->next;
	while (tmp)
	{
		if (tmp->arcw == 1)
			count++;
		tmp = tmp->next;
	}
	if (count < 1)
		node->passed_flag = 0;
	else
		node->passed_flag = 5;
}

void	ft_reset_passed_flags_gasp(t_list **list)
{
	t_list *tmp;
	t_node *node;

	tmp = *list;
	while (tmp && tmp->next)
	{
		node = (t_node *)tmp->content;
		if (node->passed_flag == 5 || node->passed_flag == -5)
			node->passed_flag = 5;
		else
			node->passed_flag = 0;
		node->chance_one = 0;
		tmp = tmp->next;
	}
}

void	ft_test_g(t_list **list)
{
	t_list *tmp;
	t_list *tmp_2;
	t_node *node;

	tmp = *list;
	ft_putchar('\n');
	while (tmp && tmp->content && ((t_node *) tmp->content)->name)
	{
		node = (t_node *) tmp->content;
		tmp_2 = node->next;
		ft_printf("%s ||", node->name);
		while (tmp_2)
		{
			node = (t_node *) tmp_2->content;
			ft_printf("-> %s:%d ", node->name, tmp_2->arcw);
			tmp_2 = tmp_2 -> next;
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
}

int	ft_connect_start(t_list **list)
{
	t_node	*start;
	t_list	*tmp;
	int	count;

	start = ft_find_t_node_with_start(list);
	tmp = start->next;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void		ft_test_flag(t_list **list)
{
	t_list *tmp;
        t_node *node;

        tmp = *list;
        ft_putchar('\n');
        while (tmp->next)
        {
                node = (t_node *) tmp->content;
		ft_printf("%s - %d -> %d\n", node->name, node->passed_flag, node->chance_one);
                tmp = tmp->next;
        }
	ft_putchar('\n');
}

t_list		***ft_malloc_result(t_params **params, t_list **list)
{
	int     size;
	int     i;
	t_list	***result;

	i = -1;
	if ((*params)->ant_count >= ft_connect_start(list))
		size = ft_connect_start(list);
	else
		size = (*params)->ant_count;
	if (!(result = (t_list ***)malloc(sizeof(t_list *) * (size + 1))))
		return (NULL);
	return (result);
}

void    print_bibli(t_list ***result, int i)
{
        t_node  *node;
        t_list  *tmp;
        int     j;

        j = -1;
        ft_printf("\n");
        while (++j <= i)
        {
                node = (t_node *)((*result)[j]->content);
                ft_printf("%s ", node->name);
                tmp = (*result)[j]->next;
                while (tmp)
                {
                        node = (t_node *) tmp->content;
                        ft_printf("-> %s ", node->name);
                        tmp = tmp->next;
                }
                ft_printf("\n");
        }
}

void	ft_algo(t_params **params, t_list **list)
{
	t_node	*node;
	int	index;
	t_list	***result;

	index = 0;
	node = ft_find_t_node_with_start(list);
	result = ft_malloc_result(params, list);
	while (index < (*params)->ant_count && index < ft_connect_start(list) && ft_bfs_gaspard(list, params, node) > 0)
	{
		if (!(result[index] = (t_list **)malloc(sizeof(t_list) * (index + 1))))
			return ;
		//ft_test_flag(list);
		ft_reset_passed_flags_gasp(list);
		//ft_test_g(list);
		ft_put_bibli(list, result, index);
		index++;
	}

	int	l = -1;                      // test
	while (++l < index)                  // test
        	print_bibli(&result[l], l);  // test
}
