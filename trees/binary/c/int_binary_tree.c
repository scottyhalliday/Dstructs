/*
 * INT_BINARY_TREE.C
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an integer binary tree.  
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
#include "include/int_binary_tree.h"

// ----------------------------------------------------------------------------
struct TreeNode* 
create_new_node(int value)
{
    struct TreeNode *new_node;

    new_node = (struct TreeNode *) malloc(sizeof(struct TreeNode));    
    
    new_node->parent      = NULL;
    new_node->left_child  = NULL;
    new_node->right_child = NULL;
    
    new_node->data    = value;
    new_node->is_null = FALSE;

    return new_node;

}

// ----------------------------------------------------------------------------
// Create a NULL (Dummy) node.  This serves as a way to pass NULL children to
// the print queue.
struct TreeNode* 
create_null_node(int value, struct TreeNode *parent)
{
    struct TreeNode *new_node;

    new_node = (struct TreeNode *) malloc(sizeof(struct TreeNode));    
    
    new_node->parent      = parent;
    new_node->left_child  = NULL;
    new_node->right_child = NULL;
    
    new_node->data    = value;
    new_node->is_null = TRUE;

    return new_node;

}


// ----------------------------------------------------------------------------
// Delete a value from the tree.  Returns 1 if the value was succesfully deleted
// otherwise a 0 is returned indicating that the value did not exist so it could
// not be deleted
int
delete_node(int value)
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

    free(node);

    return TRUE;

}

void
rearrange_nodes(struct TreeNode *lnode, struct TreeNode *rnode)
{

    struct TreeNode* node;

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
fetch_node(struct TreeNode *node, int value)
{
    struct TreeNode* left_node;
    
    if (node == NULL)
    {
        return NULL_NODE;
    }

    if (node->data == value)
    {
        return node;
    }

    left_node = fetch_node(node->left_child , value);
    return left_node->data == value ? left_node : fetch_node(node->right_child, value);
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
void
initialize_binary_tree()
{
    ROOT           = NULL;
    NULL_NODE      = create_null_node(0,NULL);
    NUM_TREE_NODES = 0;
}

// ----------------------------------------------------------------------------
// Since this implementation is an arbitrary binary tree insertion does not
// have any required order.  So this will add new nodes from the left child to
// the right child working down the tree height.  No duplicates are allowed.
int
insert_node(int value) 
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
        return 0;
    }

    // Start at the root
    current_node = ROOT;

    // Make sure the item does not already exist
    exists = value_exists(current_node, value);

    if (exists == TRUE) 
    {
        printf("ERROR:  Value '%d' already exists in the tree.  No duplicates allowed.\n", value);
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
    int data;
    int depth;
    int this_level;
    int is_null_node;

    // Node queue
    int    tot_nodes;
    int    qsize;
    int    nsize;
    struct TreeNode **queue;
    struct TreeNode **null_stack;
    struct TreeNode *this_node;
    struct TreeNode *null_node;

    // Determine the print spacing for each level of the tree
    depth = tree_depth(ROOT);

    // Intialize each levels print spacing
    pre_spacing = (int *) calloc(depth, sizeof(int));
    mid_spacing  = (int *) calloc(depth, sizeof(int));

    // Calculate the number of nodes based on actual tree levels.  (NOTE: This 
    // will count NULL children)
    num_nodes = pow(2, depth-1);

    // Calculate the total number of possible nodes
    tot_nodes = pow(2,depth);

    //
    // Calculate the spacing of characters for each level based on tree's maximum depth
    //
    cformat   = 5;
    max_chars = cformat*num_nodes + num_nodes-1;

    // Initialize the string array which will draw the tree leader lines
    leader_lines = (char *) malloc(sizeof(char)*max_chars);

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
                queue[qsize] = create_null_node(0, this_node);
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
                queue[qsize] = create_null_node(0, this_node);
                qsize++;
            }
        }
        else if (is_null_node == TRUE && this_level < depth)
        {
            queue[qsize] = create_null_node(0, this_node);
            qsize++;

            queue[qsize] = create_null_node(0, this_node);
            qsize++;

        }

        // Print the pre spacing if this is the start of a new line
        if (nprint == 0) 
        {
            for (i=0; i<pre_spacing[this_level-1]; i++) {
                printf(" ");
            }
        }

        if (this_level <= depth) {
            if (is_null_node == TRUE)
            {
                for (i=0; i<cformat; i++)
                {   
                    printf(" ");
                }
            }
            else
            {
                printf("%5d", data);
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
        }

        // Print mid-spacing
        for (i=0; i<mid_spacing[this_level-1]; i++)
        {
            printf(" ");
        }
        nprint++;

        // Move to a new line?
        if (nprint >= pow(2, this_level-1)) 
        {
            printf("\n");
            nprint = 0;
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

        // If this node was NULL node then free its memory.  It has served its purpose
        if (is_null_node == TRUE) {
            //free(this_node);
        }

    }

    // Finally print a new line
    printf("\n");

    // Cleanup
    free(queue);
    free(pre_spacing);
    free(mid_spacing);
    free(leader_lines);

}

// ----------------------------------------------------------------------------
// Returns True if the value is in the tree starting at a give node, False
// otherwise.
int
value_exists(struct TreeNode *node, int value) 
{
    if (node == NULL)
    {
        return FALSE;
    }
    else if (node->data == value)
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
    int i;
    int result;
    struct TreeNode *node;

    printf("C Implementation of Integer Binary Tree\n");

    initialize_binary_tree();

    // Build the tree
    for (i=1; i<=21; i++) {
        insert_node(i);
    }

    result = value_exists(ROOT,1);
    printf("result = %d\n", result);


    printf("Number of nodes is %d\n", NUM_TREE_NODES);
    print_tree();

    printf("Fetching 6 from the tree\n");
    node = fetch_node(ROOT,6);
    printf("node->data = %d\n", node->data);

    printf("Fetching 26 from the tree\n");
    if (value_exists(ROOT, 26))
    {
        node = fetch_node(ROOT,26);
    }

    delete_node(16);
    print_tree();


    delete_node(9);
    print_tree();


    delete_node(4);
    print_tree();

    delete_node(5);
    print_tree();

    delete_node(20);
    print_tree();

    delete_node(6);
    print_tree();

    delete_node(21);
    print_tree();

    delete_node(1);
    print_tree();

    delete_node(17);
    print_tree();

    delete_node(7);
    print_tree();

    delete_node(15);
    print_tree();

    insert_node(15);
    print_tree();

    insert_node(150);
    print_tree();

    delete_node(2);
    print_tree();

    delete_node(8);
    print_tree();

    delete_node(18);
    print_tree();

    delete_node(19);
    print_tree();

    delete_node(15);
    print_tree();

    delete_node(10);
    print_tree();

    delete_node(11);
    print_tree();

    delete_node(150);
    print_tree();

    delete_node(3);
    print_tree();

    delete_node(12);
    print_tree();

    delete_node(13);
    print_tree();

    delete_node(14);
    print_tree();

}