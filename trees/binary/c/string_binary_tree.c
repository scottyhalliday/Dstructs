/*
 * STRING_BINARY_TREE.C
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of string binary tree.  
 *
 * This implementation is simply a conceptual binary tree.  It does not follow
 * the deletion and insertion rules of any one type of binary tree (BST, AVL, etc)
 * The left child has precedence in insertion and deletion.  That means there 
 * will always be a left child before a right child.  There is no specific reason
 * other than I had to choose something.  
 * 
 * This implementation helps to explore the concepts of tree such as it's left
 * and right children, the parent node, tree depth, tree level, etc.  These 
 * features will be used to develop more advanced and efficient trees.
 * 
 * ****R E F R E S H E R   B L O C K ******************************************
 * For a refresher recall how the '.' and '->' notations are used within C.  
 * '->' is used as a shorthand for a pointer to a variable type struct.  
 * For example, suppose I have the following:
 *
 *     struct this_struct {
 *        int attr;   
 *     }
 *     
 *     struct this_struct *my_struct;
 *     
 * Must initialize the memory where the 'my_struct' is pointing
 *     
 *     my_struct = (struct this_struct *) malloc(sizeof(struct this_struct)); *     
 *     
 * To access the member of the struct and considering my_struct is a pointer,    
 * I would do the following.
 *     
 *     (*my_struct).attr = 100;
 * 
 * Or you can use the convenient '->'    
 *     
 *     my_struct->attr = 100;
 *     
 * Now suppose I don't make a pointer declaration but instead make an actual
 * variable declaration.  Instead of doing this,
 *
 *     struct this_struct *my_struct;
 *
 * I do this,
 *
 *     struct this_struct my_struct;
 *
 * Since this is no longer a pointer declaration we don't need to worry about
 * the address that the pointer points to we can go back to the '.' notation
 * like was seen above since we don't need to include the pointer reference.
 * So I can set the value 'attr' as follows.
 *
 *     my_struct.attr = 100;
 * 
 * I jump between programming languages and I usually forget these minor but
 * important details.  So this will help refresh my memory.
 * 
 * Since we are building a linked list we will want to work with pointers so
 * we can 'point' to other nodes!! 
 * ****************************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "include/string_binary_tree.h"

// ----------------------------------------------------------------------------
// Cleanup the binary tree and the memory it consumes
void
cleanup_binary_tree()
{
    // Delete the tree if not done so already
    delete_tree();

    // Free global NULL node
    free(NULL_NODE->data);
    free(NULL_NODE);
}

// ----------------------------------------------------------------------------
struct TreeNode* 
create_new_node(char *value)
{
    struct TreeNode *new_node;

    new_node = (struct TreeNode *) malloc(sizeof(struct TreeNode));    

    // Allocate memory for the string itself
    new_node->data = (char *) calloc(strlen(value)+1, sizeof(char));
    strcpy(new_node->data, value);

    new_node->parent      = NULL;
    new_node->left_child  = NULL;
    new_node->right_child = NULL;
    
    new_node->is_null = FALSE;

    return new_node;

}

// ----------------------------------------------------------------------------
// Create a NULL (Dummy) node.  This serves as a way to pass NULL children to
// the print queue.
struct TreeNode* 
create_null_node(char *value, struct TreeNode *parent)
{
    struct TreeNode *new_node;

    new_node = (struct TreeNode *) malloc(sizeof(struct TreeNode));    

    // Allocate memory for the string itself
    new_node->data = (char *) calloc(strlen(value)+1, sizeof(char));
    strcpy(new_node->data, value);
    
    new_node->parent      = parent;
    new_node->left_child  = NULL;
    new_node->right_child = NULL;
    
    new_node->is_null = TRUE;

    return new_node;

}

// ----------------------------------------------------------------------------
// Delete a value from the tree.  Returns 1 if the value was succesfully deleted
// otherwise a 0 is returned indicating that the value did not exist so it could
// not be deleted
int
delete_node(char *value)
{

    struct TreeNode* parent;
    struct TreeNode* node;

    if (value_exists(ROOT, value) == FALSE)
    {
        return FALSE;
    }

    // Get the node to delete and its parent node
    node = fetch_node(ROOT,value);
    
    if (node == ROOT)
    {   
        if (node->left_child != NULL)
        {
            ROOT = node->left_child;
            node->left_child->parent = NULL;
            rearrange_nodes(node->left_child, node->right_child);
        } 
        else if (node->right_child != NULL)
        {
            ROOT = node->right_child;
            node->right_child->parent = NULL;
            rearrange_nodes(node->left_child, node->right_child);
        }
        else
        {
            ROOT = NULL;
        }
    }
    else
    {
        parent = node->parent;
    
        // Reassign the child connection to new node
        if (parent->left_child == node)
        {
            if (node->left_child != NULL)
            {
                // Reassign the parent node to point to the left child of the deleted node
                parent->left_child       = node->left_child;
                node->left_child->parent = parent;
                rearrange_nodes(node->left_child, node->right_child);
            } 
            else 
            {
                // Make sure we preserve left child precedence
                if (parent->right_child != NULL)
                {
                    parent->left_child  = parent->right_child;
                    parent->right_child = NULL;
                }
                else
                {
                    parent->left_child = NULL;
                }
            }
        }
        else
        {
            if (node->left_child != NULL)
            {
                // Reassign the parent node to point the left child of deleted node
                parent->right_child = node->left_child;
                node->left_child->parent = parent;
                rearrange_nodes(node->left_child, node->right_child);
            }
            else
            {
                parent->right_child = NULL;
            }
        }
    }

    // Decrement the master node counter
    NUM_TREE_NODES--;

    // Free the memory the deleted node occupied
    free(node->data);
    free(node);

    return TRUE;

}

// ----------------------------------------------------------------------------
// Deletes the tree and frees all associated memory.  This delete process
// firsts visits every node and adds them to a stack.  Then once all nodes are
// discovered their memory is freed and the ROOT is set back to NULL.  This
// is a more efficient means to delete the tree instead of deleting each node
// and rearranging the tree.
int
delete_tree()
{

    int size;
    struct TreeNode *node;
    struct TreeNode **stack;

    // If tree is empty then nothing to do here
    if (ROOT == NULL)
    {
        return TRUE;
    }

    // Add each node to delete to the stack
    stack = (struct TreeNode**) malloc(sizeof(struct TreeNode *)*NUM_TREE_NODES);
    size = 0;

    stack[0] = ROOT;
    size++;

    while (size != 0)
    {

        // Pop the next node from the stack
        node = stack[size-1];
        size--;

        if (node->left_child != NULL)
        {
            stack[size] = node->left_child;
            size++;
        }

        if (node->right_child != NULL)
        {
            stack[size] = node->right_child;
            size++;
        }

        // Free the memory
        free(node->data);
        free(node);
    }

    // Free the memory for the stack
    free(stack);

    // Reset the master counter and reset ROOT
    NUM_TREE_NODES = 0;
    ROOT = NULL;

    return TRUE;

}

// ----------------------------------------------------------------------------
// Rearranges the nodes keeping left child precendence in mind.  Upon node
// deletion the nodes must be rearranged so that the tree remains intact.
void
rearrange_nodes(struct TreeNode *lnode, struct TreeNode *rnode)
{

    // If either of the nodes passed are NULL then there is nothing to do
    if (lnode == NULL || rnode == NULL)
    {
        return;
    }

    if (lnode->left_child == NULL)
    {
        lnode->left_child = rnode;
        rnode->parent     = lnode;
        return;
    }
    else if (lnode->right_child == NULL)
    {
        lnode->right_child = rnode;
        rnode->parent      = lnode;
        return;        
    }

    if (lnode->left_child != NULL)
    {
        if (lnode->right_child != NULL)
        {
            rearrange_nodes(lnode->left_child, lnode->right_child);
            lnode->right_child = rnode;
            rnode->parent      = lnode;
        }
    }

}

// ----------------------------------------------------------------------------
// Find a node in the tree given a value and starting node.  This function 
// assumes that a node with the given value exists.  It is the responsibility
// of the programmer to ensure value exists prior to fetching the node
struct TreeNode* 
fetch_node(struct TreeNode *node, char *value)
{
    struct TreeNode* left_node;
    
    if (node == NULL)
    {
        return NULL_NODE;
    }

    if (strcmp(node->data, value) == 0)
    {
        return node;
    }

    left_node = fetch_node(node->left_child , value);
    return strcmp(left_node->data,value) == 0 ? left_node : fetch_node(node->right_child, value);
}

// ----------------------------------------------------------------------------
// Find an open leaf (position) to place a new node for the given node.  This 
// binary tree implementation has an arbitrary node placement schema.  It fills
// open node leaves from the left to the right, level by level.
struct TreeNode* 
find_open_leaf(struct TreeNode* node)
{

    int left_depth;
    int right_depth;

    if (node->left_child == NULL || node->right_child == NULL)
    {
        return node;
    }
    else {
        
        left_depth  = tree_depth(node->left_child);
        right_depth = tree_depth(node->right_child);

        if (left_depth == right_depth)
        {
            if (node_is_full(node->left_child) == FALSE) {
                return find_open_leaf(node->left_child);
            }
            else if (node_is_full(node->left_child) == TRUE && node_is_full(node->right_child) == FALSE)
            {
                return find_open_leaf(node->right_child);
            } else 
            {
                return find_open_leaf(node->left_child);
            }
        }
        else
        {
            if (node_is_full(node->left_child) == TRUE)
            {
                return find_open_leaf(node->right_child);
            }
            else
            {
                return find_open_leaf(node->left_child);
            }
        }
    }
}

// ----------------------------------------------------------------------------
// Return the number of nodes in the tree
int 
get_number_of_nodes()
{
    return NUM_TREE_NODES;
}

// ----------------------------------------------------------------------------
void
initialize_binary_tree()
{
    ROOT           = NULL;
    NULL_NODE      = create_null_node("null",NULL);
    NUM_TREE_NODES = 0;
}

// ----------------------------------------------------------------------------
// Since this implementation is an arbitrary binary tree insertion does not
// have any required order.  So this will add new nodes from the left child to
// the right child working down the tree height.  No duplicates are allowed.
int
insert_node(char *value) 
{
    int    exists;
    struct TreeNode *current_node;
    struct TreeNode *new_node;

    // Assign the value to the new node
    new_node = create_new_node(value);

    // If the tree is empty set 
    if (ROOT == NULL)
    {
        ROOT = new_node;
        NUM_TREE_NODES++;
        return 0;
    }

    // Start at the root
    current_node = ROOT;

    // Make sure the item does not already exist
    exists = value_exists(current_node, value);

    if (exists == TRUE) 
    {
        printf("ERROR:  Value '%s' already exists in the tree.  No duplicates allowed.\n", value);
        printf("ERROR:  Quitting\n\n");
        exit(-1);
    }

    // Find a free node to attach this to
    current_node = find_open_leaf(ROOT);

    if (current_node->left_child == NULL)
    {
        current_node->left_child = new_node;
    }
    else
    {
        current_node->right_child = new_node;
    }

    // Assign this node's parent
    new_node->parent = current_node;

    // Track the number of nodes in the tree
    NUM_TREE_NODES++;

    return 1;
}

// ----------------------------------------------------------------------------
// Determine if a tree node is full.  A tree node is considered full when all
// of its children have a left and right child or the left and right children
// at the furthest depth have no children.
int
node_is_full(struct TreeNode *node)
{

    int left_depth;
    int right_depth;

    // Get the depth of each child's sub-tree
    left_depth  = tree_depth(node->left_child);
    right_depth = tree_depth(node->right_child);

    // A tree is considered full if both children of a node are NULL
    if (node->left_child == NULL && node->right_child == NULL)
    {
        return(left_depth == right_depth);
    }

    // A tree is considered full if the node has right and left children
    if (node->left_child != NULL && node->right_child != NULL)
    {
        return(node_is_full(node->left_child) && node_is_full(node->right_child) && left_depth == right_depth);
    }

    return FALSE;

}

// ----------------------------------------------------------------------------
int
node_level(struct TreeNode *node)
{
    int count = 1;

    while (node->parent != NULL) 
    {
        count++;
        node = node->parent;
    }

    return count;
}

// ----------------------------------------------------------------------------
void
print_tree()
{
    // Basic counters
    int i,j;

    // Spacing and formatting for printing nodes at each tree level
    int  nprint;
    int  cformat;
    int  bchars;
    int  max_chars;
    int  num_nodes;
    int  left_leader;
    int  right_leader;
    int  *pre_spacing;
    int  *mid_spacing;
    char *leader_lines;

    // Convenience variables
    int depth;
    int this_level;
    int is_null_node;
    char *data;

    // Node queue
    int    tot_nodes;
    int    qsize;
    int    nsize;
    struct TreeNode **queue;
    struct TreeNode **null_stack;
    struct TreeNode *this_node;

    // Determine the print spacing for each level of the tree
    depth = tree_depth(ROOT);

    // Print summary of tree
    printf("-------------------------------------------------------------------\n");
    printf("Current Tree Structure\n");
    printf("Tree Depth: %d\n", depth);
    printf("Tree Nodes: %d\n\n", NUM_TREE_NODES);

    // If tree is empty then we are done
    if (depth == 0)
    {
        printf("Tree is empty\n");
        return;
    }

    // Intialize each levels print spacing
    pre_spacing = (int *) calloc(depth, sizeof(int));
    mid_spacing = (int *) calloc(depth, sizeof(int));

    // Calculate the number of nodes based on actual tree levels.  (NOTE: This 
    // will count NULL children)
    num_nodes = pow(2, depth-1);

    // Calculate the total number of possible nodes
    tot_nodes = pow(2,depth);

    //
    // Calculate the spacing of characters for each level based on tree's maximum depth
    //
    cformat   = 5; // Keep string lengths below 5
    max_chars = cformat*num_nodes + num_nodes-1;

    // Initialize the string array which will draw the tree leader lines
    leader_lines = (char *) malloc(sizeof(char)*(max_chars+1));

    for (i=0; i<max_chars; i++)
    {
        leader_lines[i] = ' ';
    }

    // Calculate the formatting for each level
    for (i=0; i<depth; i++)
    {
        bchars         = max_chars - cformat*pow(2,i);
        mid_spacing[i] = ceil(bchars/pow(2,i));
        pre_spacing[i] = 0.5*(bchars - mid_spacing[i]*(pow(2,i)-1));

        //printf("level %d: max_chars: %d, bchars: %d, pre_spacing: %d, mid_spacing: %d\n", i, max_chars, bchars, pre_spacing[i],mid_spacing[i]);
    }

    // Initialize a queue to track left and right children
    queue = (struct TreeNode **) malloc(sizeof(struct TreeNode*)*tot_nodes);
    
    // Start at the ROOT
    queue[0] = ROOT;
    qsize    = 1;

    // Initialize a null stack to store null nodes so we can clean them up later
    null_stack = (struct TreeNode **) malloc(sizeof(struct TreeNode*)*tot_nodes);
    nsize      = 0;

    j = 0;
    nprint = 0;
    while (qsize > 0)
    {
        // Get the next node and its attributes
        this_node    = queue[0];
        data         = this_node->data;
        this_level   = node_level(this_node);
        is_null_node = this_node->is_null;

        // If a null node then add it to the null stack for cleanup later
        if (is_null_node == TRUE)
        {
            null_stack[nsize] = this_node;
            nsize++;
        }

        // Update the queue by shifting everything over
        if (qsize == 1) {
            qsize--;
        }
        else
        {
            for (i=1; i<qsize; i++)
            {
                queue[i-1] = queue[i];
            }
            qsize--;
        }

        // If the tree only consists of the root then print it and quit
        if (this_node == ROOT && NUM_TREE_NODES == 1)
        {
            printf("%5s\n\n", data);
            break;
        }

        // Put the children on the queue (If they are dummy children)
        if (is_null_node == FALSE)
        {
            // Left child
            if (this_node->left_child != NULL) 
            {
                queue[qsize] = this_node->left_child;
                qsize++;
            }
            else
            {
                queue[qsize] = create_null_node("null", this_node);
                qsize++;
            }

            // Right child
            if (this_node->right_child != NULL) 
            {
                queue[qsize] = this_node->right_child;
                qsize++;
            }
            else
            {
                queue[qsize] = create_null_node("null", this_node);
                qsize++;
            }
        }
        else if (is_null_node == TRUE && this_level < depth)
        {
            queue[qsize] = create_null_node("null", this_node);
            qsize++;

            queue[qsize] = create_null_node("null", this_node);
            qsize++;

        }

        if (this_level <= depth) {
            
            // Print the pre spacing if this is the start of a new line
            if (nprint == 0) 
            {
                for (i=0; i<pre_spacing[this_level-1]; i++) {
                    printf(" ");
                }
            }

            if (is_null_node == TRUE)
            {
                for (i=0; i<cformat; i++)
                {   
                    printf(" ");
                }
            }
            else
            {
                printf("%5s", data);
            }

            if (this_level < depth) 
            {
                // Pre-spacing
                if (nprint == 0)
                {
                    for (i=0; i<pre_spacing[this_level]+cformat-1; i++)
                    {
                        leader_lines[j] = ' ';
                        j++;
                    }    
                }
                
                // Mid-spacing 
                left_leader  = ceil(mid_spacing[this_level]/2.0)+1;
                right_leader = mid_spacing[this_level] - left_leader;
                if (this_node->left_child != NULL)
                {
                    for (i=0; i<left_leader; i++)
                    {
                        leader_lines[j] = '-';
                        j++;
                    }
                }
                else
                {
                    for (i=0; i<left_leader; i++)
                    {
                        leader_lines[j] = ' ';
                        j++;
                    }    
                }
                
                if (this_node->right_child != NULL)
                {
                    for (i=0; i<right_leader+cformat; i++)
                    {
                        leader_lines[j] = '-';
                        j++;
                    }    
                }
                else
                {
                    for (i=0; i<right_leader+cformat; i++)
                    {
                        leader_lines[j] = ' ';
                        j++;
                    }    
                }
                
                // Write spaces to next subtree
                if (nprint != pow(2,this_level-1)-1)
                {
                    for (i=0; i<mid_spacing[this_level]+cformat; i++)
                    {
                        leader_lines[j] = ' ';
                        j++;
                    }
                }
            }

            // Print mid-spacing
            for (i=0; i<mid_spacing[this_level-1]; i++)
            {
                printf(" ");
            }
            nprint++;

        }

        // Move to a new line?
        if (nprint >= pow(2, this_level-1)) 
        {
            printf("\n");
            nprint = 0;

            // Terminate the leader line string
            leader_lines[j] = '\0';

            j = 0;

            // Print the leader lines
            if (this_level != depth) 
            {
                printf("%s\n", leader_lines);
            }

            // Cleanup the leader lines
            for (i=0; i<max_chars; i++)
            {
                leader_lines[i] = ' ';
            }   
        }
    }

    // Finally print a new line
    printf("\n");

    // Cleanup
    free(queue);
    free(pre_spacing);
    free(mid_spacing);
    free(leader_lines);

    for (i=0; i<nsize; i++)
    {
        free(null_stack[i]->data);
        free(null_stack[i]);
    }
    free(null_stack);

}

// ----------------------------------------------------------------------------
// Returns True if the value is in the tree starting at a give node, False
// otherwise.
int
value_exists(struct TreeNode *node, char *value) 
{
    if (node == NULL)
    {
        return FALSE;
    }
    else if (strcmp(node->data,value) == 0)
    {
        return TRUE;
    }
    else
    {
        return value_exists(node->left_child,value) || value_exists(node->right_child, value);
    }
}

// ----------------------------------------------------------------------------
int
tree_depth(struct TreeNode *node)
{
    int depth_left;
    int depth_right;

    if (node == NULL)
    {
        return 0;
    }

    // Get the depth for this node's children
    depth_left  = tree_depth(node->left_child);
    depth_right = tree_depth(node->right_child);

    // Return the maximum height
    if (depth_left >= depth_right)
    {
        return 1 + depth_left;
    }
    else
    {
        return 1 + depth_right;
    }

}

// ----------------------------------------------------------------------------
int 
main(int argc, char **argv)
{
    char string[4] = "only";
    struct TreeNode *node;

    printf("\n\nC Implementation of Integer Binary Tree\n\n");

    // Initialize the binary tree.  This sets some global variables used by the
    // binary tree instance.  Failure to call this will result in errors
    initialize_binary_tree();

    insert_node("hi");
    insert_node("I");
    insert_node("can");
    insert_node("only");
    insert_node("have");
    insert_node("five");
    insert_node("char");
    insert_node("word");
    insert_node("cuz");
    insert_node("of");
    insert_node("tree");
    insert_node("echo");

    print_tree();

    printf("\n\nLet's remove the word 'char' from the tree\n");
    delete_node("char");
    print_tree();

    printf("\n\nLet's remove the root from the tree\n");
    delete_node("hi");
    print_tree();

    printf("\n\nLet's insert the word 'quit' into the tree\n");
    insert_node("quit");
    print_tree();

    printf("\n\nLet's find the node with the word 'only'...Should work\n");
    node = fetch_node(ROOT, string);
    printf("Searching for node 'only', found node '%s'\n", node->data);

    // Build the tree applying random values
    cleanup_binary_tree();
}