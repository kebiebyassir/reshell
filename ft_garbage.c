#include "include/minishell.h"

void	gc_init(t_gc *gc)
{
	if (gc)
		gc->head = NULL;
}

void	*gc_saver(void *p, t_gc *gc)
{
	t_gc_list	*new;
	t_gc_list	*curr;

	if (!gc || !p)
		return (NULL);
	new = malloc(sizeof(t_gc_list));
	if (!new)
		return (NULL);
	new->ptr = p;
	new->next = NULL;
	if (!gc->head)
		gc->head = new;
	else
	{
		curr = gc->head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (p);
}

void	*gc_malloc(size_t size, t_gc *gc)
{
	void	*p;

	if (!gc)
		return (NULL);
	p = malloc(size);
	if (!p)
		return (NULL);
	return (gc_saver(p, gc));
}

void	gc_free(t_gc *gc)
{
	t_gc_list	*tmp;

	if (!gc)
		return;
	while (gc->head)
	{
		tmp = gc->head;
		free(tmp->ptr);
		gc->head = tmp->next;
		free(tmp);
	}
}
