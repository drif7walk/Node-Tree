/*
A node tree structure where every node can have an unspecified
number of child nodes

Don't mind the warnings about uninitialized nodes,
When declared a pointer is undefined, that means that it
exists as a number, however the number has not been set yet.
When NewNode is called then the number, or, pointer value of the
newly declared Node is set to what ever malloc returns that is
a number (pointer) to the block of memory malloc() just freed.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char* name;
	struct Node* children;
	struct Node* parent;
	struct Node* next;
	void (*updateSelf)(struct Node* self);
};
typedef struct Node Node;

Node* NewNode()
{
    Node* n = NULL;

    // Semi-voodoo
    int ec = 0;
    while (n == NULL)
    {
            n = malloc(sizeof(Node));
            ec++;
            if (ec >= 3)
            {
                exit(1);
            }
    }

    n->name = "unnamed";
    n->children = NULL;
    n->parent = NULL;
    n->next = NULL;
    n->updateSelf = NULL;

    return n;
}


void TraverseTree(Node* parent)
{
    Node* current = parent;

    while(1)
    {
        /* Do updating/process node */
        if (current->updateSelf != NULL)
            current->updateSelf(current);

        if (current->next != NULL)
        {
                current = current->next;
                if (current->children != NULL)
                    TraverseTree(current->children);
        }
        else
            break;
    }
}

/*
Node* GetLastNodeInLine(Node* n)
-
Find the node after which there is no "next".
*/
Node* GetLastNodeInLine(Node* n)
{

    Node* current = n;
    while(1)
    {
        if (current->next == NULL)
            return current;
        else current = current->next;
    }
}

/*
void AddNode(Node* n)
-
Finds the last node and adds n as its next.
*/
void AddNode(Node* target, Node* n)
{
    Node* last = GetLastNodeInLine(target);
    last->next = n;
}

/*
Frees all the resources and invalidates pointer.
*/
void DestroyNode(Node* n)
{
    free(n->name);
    free(n);
}

void FreeNodes(Node* rootNode)
{
    Node* current = rootNode;

    while(1)
    {
        if (current->next != NULL)
        {
                Node* tofree = current;
                current = current->next;
                if (current->children != NULL)
                    FreeNodes(current->children);
                free(tofree);
        }
        else
            break;
    }
    free(current);
    current = NULL;
}

void _updateSelf(Node* self)
{
    printf("self name: %s\r\n", self->name);
}

int main()
{
    Node* root = NewNode();
    root->name = "root node";
    root->updateSelf = _updateSelf;

    Node* firstchild = NewNode();
    firstchild->name = "first child";

    Node* childschild = NewNode();
    childschild->name = "childs child";
    childschild->updateSelf = _updateSelf;

    AddNode(root, firstchild);
    AddNode(firstchild, childschild);

    TraverseTree(root);

    FreeNodes(root);

    return 0;
}


