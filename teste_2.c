#include <stdlib.h>
#include <string.h>

struct g_node {
	const char *name;
	struct g_node **links;
	int nlinks, clinks;
};

struct g_link {
	struct g_node *end1, *end2;
	unsigned int distance;
};

/* proto */
struct g_node *createnode(const char *);
struct g_link *createlink(struct g_node *, struct g_node *, int);

/*
 * Funções meio que inerentes ao grafo.
 */

struct g_node
*createnode(const char *name)
{
	struct g_node *newnode = NULL;

	newnode = malloc(sizeof (struct g_node));
	newnode->name = strdup(name);

	newnode->links = malloc(5 * sizeof (struct g_node *));
	newnode->clinks = 5;
	newnode->nlinks = 0;

	return newnode;
}

struct g_link
*createlink(struct g_node *end1, struct g_node *end2, int distance)
{
	struct g_link *link = NULL;

	link = malloc(sizeof (struct g_link));
	link->end1 = end1;
	link->end2 = end2;
	link->distance = distance;

	if (end1->nlinks >= end1->clinks) {
		end1->links = realloc(end1->links, end1->clinks + 5);
		end1->clinks += 5;
	}
	if (end2->nlinks >= end2->clinks) {
		end2->links = realloc(end2->links, end2->clinks + 5);
		end2->clinks += 5;
	}

	end1->links[end1->nlinks++] = end2;
	end2->links[end2->nlinks++] = end1;

	return link;
}

int
arelinked(struct g_node *a, struct g_node *b)
{
	return arelinkedr(a, a, b);
}

int
arelinkedr(struct g_node *origin, struct g_node *current, struct g_node *needle)
{
	int found = 0;
	int i;

	if (current == needle)
		return 1;

	for (i = 0; i < current->nlinks; ++i) {
		if (current->links[i] != origin)
			found += arelinkedr(current, current->links[i], needle);
	}

	return found > 0;
}

/*
 * Funções cujo propósito é executar o algoritmo de Kruskal.
 */

void
kruskal(struct g_link **links, int nlinks, struct g_link **newlinks,
		struct g_node **nodes, int nnodes)
{
	struct g_node *end1, *end2;
	int i, j;

	// ordena os links originais
	qsort(links, nlinks, sizeof(struct g_link *), &comparelinks);

	// reseta todos os links dos nós para criar novos
	for (i = 0; i < nnodes; ++i)
		nodes[i]->nlinks = 0;

	// obs: é esperado que newlinks tenha tamanho suficiente
	for (i = 0; i < nlinks; ++i) {
		if (!arelinked(links[i]->end1, links[i]->end2))
			*(newlinks++) = createlink(links[i]->end1, links[i]->end2);
	}
}

int
comparelinks(const void *l1, const void *l2)
{
	struct g_link *link1 = l1;
	struct g_link *link2 = l2;

	if (link1->distance != link2->distance)
		return link1->distance - link2->distance;
	else
		return strcmp(link1->end1->name, link2->end1->name) ||
			strcmp(link1->end2->name, link2->end2->name);
}

/*
 * main de exemplo
 */

int
main(void)
{
	struct g_node **nodes = NULL;
	struct g_link **links = NULL;
	struct g_link **klinks = NULL;
	int nnodes = 5;
	int i;

	nodes = malloc(nnodes * sizeof(struct g_node *));

	// adiciona as nodes
	for (i = 0; i < nnodes; ++i)
		nodes[i] = createnode("XYZ");

	links = malloc(10 * sizeof(struct g_link *));

	// adiciona uns links
	for (i = 0; i < 10; ++i)
		links[i] = createlink(nodes[0], nodes[2], 50);

	klinks = malloc((nnodes - 1) * sizeof(struct g_node *));

	kruskal(links, 10, klinks, nodes, nnodes);

	return 0;
}


