/*
A node tree structure where every node can have an unspecified
number of child nodes
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char* name;
	struct Node* children;
	struct Node* parent;
	struct Node* next;

	float parentOffset[3]; // X Y Z offset from parent
};
typedef struct Node Node;

Node* NewNode(Node* n)
{
    n = malloc(sizeof(Node));
    n->name = "unnamed";
    n->children = NULL;
    n->parent = NULL;
    n->next = NULL;

    return n;
}


void TraverseTree(Node* parent)
{
    Node* current = parent;

    // Do something with the current node
    // current->Updateorwhatever();

    while(1)
    {
        printf("Current node: %s\r\n", current->name);

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
    target->next = n;
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

int main()
{
    Node* root = NewNode(root);
    root->name = "root node";

    Node* firstchild = NewNode(firstchild);
    firstchild->name = "first child";

    Node* childschild = NewNode(childschild);
    childschild->name = "childs child";

    AddNode(root, firstchild);
    AddNode(firstchild, childschild);

    TraverseTree(root);

    FreeNodes(root);

    return 0;
}
