/*
 * FLOAT_BINARY_SEARCH_TREE.C
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an floating point/double binary search tree (BST).  
 * This implementation of the binary tree uses pointers between parent and 
 * children.  This is done primarily to aid the printing of the tree itself.  
 * It allows the print algorithm to go up and down the tree to determine 
 * the tree print format.  This approach can most likely be simplified as 
 * managing pointers between children and parents can become cumbersome and 
 * error prone.  However, I find it nice to visually see the tree so I can 
 * verify it is as I expect it.
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
 * ****************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/float_binary_search_tree.h"

// ----------------------------------------------------------------------------
// Cleans up the binary tree and ensures all memory is deallocated.  This
// function is intended to be called when interacting with the tree.  This
// will terminate the run.  If you want to simply destroy the tree and start
// over, then call DESTROY_TREE()
void
cleanup_binary_tree()
{
    destroy_tree();
    free(NULL_NODE);
}


// ----------------------------------------------------------------------------
struct TreeNode* 
create_new_node(double value)
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
create_null_node(double value, struct TreeNode *parent)
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
// Delete a node from the tree and reform links between children and parent nodes
// to keep binary search tree in proper format.
struct TreeNode*
delete_node(struct TreeNode *root, double value) 
{

    struct TreeNode *temp;
    struct TreeNode *pnode;

    if (root == NULL)
    {
        return root;
    }

    pnode = root->parent;

    // If value is less than root, then move down the left subtree
    if (value < root->data)
    {
        root->left_child = delete_node(root->left_child, value);
    }
    
    // If the value is more than root, then move down right subtree
    else if (value > root->data)
    {
        root->right_child = delete_node(root->right_child, value);
    }

    // Otherwise, we have found the value
    else
    {
        if (root->left_child == NULL)
        {
            temp = root->right_child;

            if (root->right_child != NULL)
            {
                if (pnode == NULL) {
                    ROOT = root->right_child;
                    root->right_child->parent = NULL;
                }
                if (root->right_child->data > pnode->data)
                {
                    pnode->right_child = root->right_child;
                    root->right_child->parent = pnode;
                }
                else
                {
                    pnode->left_child = root->right_child;
                    root->right_child->parent = pnode;
                }
            }

            free(root);
            NUM_TREE_NODES--;
            return temp;
        }
        
        else if (root->right_child == NULL)
        {
            temp = root->left_child;
            
            if (root->left_child != NULL)
            {
                if (pnode == NULL) {
                    ROOT = root->left_child;
                    root->left_child->parent = NULL;
                }
                else if (root->left_child->data > pnode->data)
                {
                    pnode->right_child = root->right_child;
                    root->right_child->parent = pnode;
                }
                else
                {
                    pnode->left_child = root->left_child;
                    root->left_child->parent = pnode;
                }
            }
            
            free(root);
            NUM_TREE_NODES--;
            return temp;
        }

        // Can either find the min node in right subtree or max node in left
        // subtree.  This will find the min value in right subtree
        struct TreeNode *temp = find_min_node(root->right_child);

        root->data = temp->data;

        root->right_child = delete_node(root->right_child, temp->data);
    }

    return root;
}

// ----------------------------------------------------------------------------
// Destroy all nodes and reset ROOT
int
destroy_tree()
{
    int    node_cnt;

    struct TreeNode  *node;
    struct TreeNode **node_stack;

    // If tree is empty then we are done
    if (NUM_TREE_NODES == 0)
    {
        printf("Tree is empty\n");
        return TRUE;
    }

    // Initialize a null stack to store null nodes so we can clean them up later
    node_stack = (struct TreeNode **) malloc(sizeof(struct TreeNode*)*NUM_TREE_NODES);
    node_stack[0] = ROOT;
    node_cnt = 1;

    while (node_cnt > 0)
    {
        node = node_stack[node_cnt-1];
        node_cnt--;

        if (node->left_child != NULL)
        {
            node_stack[node_cnt] = node->left_child;
            node_cnt++;
        }

        if (node->right_child != NULL)
        {
            node_stack[node_cnt] = node->right_child;
            node_cnt++;
        }

        free(node);
    }

    free(node_stack);

    return TRUE;
}

// ----------------------------------------------------------------------------
// Work down a tree/subtree to find the maximum value with respect to original
// given node.
struct TreeNode*
find_max_node(struct TreeNode *node)
{
    if (node->right_child == NULL)
    {
        return node;
    }
    return find_max_node(node->right_child);
}

// ----------------------------------------------------------------------------
// Work down a tree/subtree to find the minimum value with respect to original
// given node.
struct TreeNode*
find_min_node(struct TreeNode *node)
{
    if (node->left_child == NULL)
    {
        return node;
    }
    return find_min_node(node->left_child);
}

// ----------------------------------------------------------------------------
struct TreeNode*
find_node(struct TreeNode *node, double value)
{
    if (value == node->data)
    {
        return node;
    }

    if (value > node->data)
    {
        return find_node(node->right_child, value);
    }
    return find_node(node->left_child, value);
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
// Insert a node into the binary tree.  The insertion must follow the principles
// of a binary search tree in that there will be no duplicates, the root node
// is greater than its left child but less than its right child
int
insert_node(double value)
{
    struct TreeNode *node;
    struct TreeNode *new_node;

    // If tree is empty then this value will assume the ROOT role
    if (ROOT == NULL)
    {
        ROOT = create_new_node(value);
        NUM_TREE_NODES++;
        return TRUE;
    }

    // Make sure we don't allow duplicates
    if (value_exists(ROOT, value) == TRUE)
    {
        printf("INSERT ERROR: Value '%7.2f' already exists in the tree.  No duplicates!\n", value);
        return FALSE;
    }

    // Start at the root and work our way down the tree to find a spot to insert this
    node     = find_open_spot(ROOT, value);
    new_node = create_new_node(value);

    if (value > node->data)
    {
        node->right_child = new_node;
    }
    else
    {
        node->left_child = new_node;
    }

    new_node->parent = node;
    NUM_TREE_NODES++;

    return TRUE;
}

// ----------------------------------------------------------------------------
struct TreeNode*
find_open_spot(struct TreeNode *node, double value)
{
    // Smaller values go to the left children
    if (value < node->data)
    {
        if (node->left_child == NULL)
        {
            return node;
        } 
        return find_open_spot(node->left_child, value);
    }

    // Otherwise values go the right children
    if (node->right_child == NULL)
    {
        return node;
    }
    return find_open_spot(node->right_child, value);
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
    double data;

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
    cformat   = 5;
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
            printf("%7.2f\n\n", data);
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
                printf("%7.3f", data);
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
        free(null_stack[i]);
    }
    free(null_stack);

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
// Returns True if the value is in the tree starting at a give node, False
// otherwise.
int
value_exists(struct TreeNode *node, double value) 
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
        if (value > node->data)
        {
            return value_exists(node->right_child, value);
        }
        return value_exists(node->left_child, value);
    }
}

// ----------------------------------------------------------------------------
int 
main(int argc, char **argv)
{

    int i;
    double tree[12] = {4.0,8.9,63.2,4.1,22.3,84.12,52.9,5.2,3.98,26.8,57.998,74.02};

    initialize_binary_tree();

    // Populate the tree
    for (i=0; i<12; i++)
    {
        printf("*** INSERTING %7.2f\n", tree[i]);
        insert_node(tree[i]);
        print_tree();
    }

    // Delete some of the nodes in no particular order
    for (i=0; i<12; i++)
    {
        printf("*** DELETING %7.2f\n", tree[i]);
        delete_node(ROOT, tree[i]);
        print_tree();
    }

    cleanup_binary_tree();

    return 0;
}