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
    
    new_node->level = -1;
    new_node->data  = value;

    return new_node;

}

// ----------------------------------------------------------------------------
// Finds a node that has a free spot open to insert an item adhering to this
// trees fill order.  Fill order fills left children before filling right 
// children.
struct TreeNode* 
find_free_node(struct TreeNode* node)
{

    int left_depth;
    int right_depth;

    printf("\n----------------------\n");
    printf("STATUS\n");
    printf("Current Node: %d\n", node->data);
    if (node->left_child == NULL)
    {
        printf("  Left Node   : NULL\n");
    }
    else
    {
        printf("  Left Node   : %d\n", node->left_child->data);
    }
    if (node->right_child == NULL)
    {
        printf("  Right Node  : NULL\n");
    }
    else
    {
        printf("  Right Node  : %d\n", node->right_child->data);
    }
    printf("  Left Depth  : %d\n", tree_depth(node->left_child));
    printf("  Right Depth : %d\n", tree_depth(node->right_child));

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
                printf("  Picking left child (a)\n");
                return find_free_node(node->left_child);
            }
            else if (node_is_full(node->left_child) == TRUE && node_is_full(node->right_child) == FALSE)
            {
                printf("  Picking right child (a)\n");
                return find_free_node(node->right_child);
            } else {
                printf("  Picking left child (a)\n");
                return find_free_node(node->left_child);
            }
        }
        else
        {
            if (node_is_full(node->left_child) == TRUE)
            {
                printf("  Picking right child (b)\n");
                return find_free_node(node->right_child);
            }
            else
            {
                printf("  Picking left child (b)\n");
                return find_free_node(node->left_child);
            }
        }
/*
        
        left_depth  = tree_depth(node->left_child);
        right_depth = tree_depth(node->right_child);
                
        if (left_depth == right_depth && node_is_complete(node))
        {
            printf("  Picking left child (a)\n");
            return find_free_node(node->left_child);
        }
        else if (left_depth > right_depth && node_is_complete(node->left_child))
        {
            printf("  Picking right child\n");
            return find_free_node(node->right_child);
        }
        else 
        {
            printf("  Picking left child (b)\n");
            return find_free_node(node->left_child);
        }
        if (tree_depth(node->left_child) >= tree_depth(node->right_child) && node_is_complete(node->left_child))
        {
            return find_free_node(node->right_child);
        }
        else
        {
            return find_free_node(node->left_child);
        }
*/
    }

}

// ----------------------------------------------------------------------------
void
initialize_binary_tree()
{
    ROOT = NULL;
}

// ----------------------------------------------------------------------------
// Since this implementation is an arbitrary binary tree insertion does not
// have any required order.  So this will add new nodes from the left child to
// the right child working down the tree height.  No duplicates are allowed.
int
insert(int value) 
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
        new_node->level=0;
        return 0;
    }

    // Start at the root
    current_node = ROOT;

    // Make sure the item does not already exist
    exists = search_tree(current_node, value);

    if (exists == TRUE) 
    {
        printf("ERROR:  Value '%d' already exists in the tree.  No duplicates allowd.\n", value);
        printf("ERROR:  Quitting\n\n");
        exit(-1);
    }

    // Find a free node to attach this to
    current_node = find_free_node(ROOT);

    if (current_node->left_child == NULL)
    {
        printf("Adding %d to left child of node %d\n", value, current_node->data);
        current_node->left_child = new_node;
    }
    else
    {
        printf("Adding %d to right child of node %d\n", value, current_node->data);
        current_node->right_child = new_node;
    }

    // Update the level of the node
    new_node->level = current_node->level + 1;

    return 1;
}

// ----------------------------------------------------------------------------
// A tree node is complete if it has both left and right child nodes
int
node_is_complete(struct TreeNode *node)
{
    if (node->left_child != NULL && node->right_child != NULL)
    {
        return TRUE;
    }

    return FALSE;
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
// Returns True if the value is in the tree starting at a give node, False
// otherwise.
int
search_tree(struct TreeNode *node, int value) 
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
        return search_tree(node->left_child,value) || search_tree(node->right_child, value);
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
    int result;
    struct TreeNode *tree;

    printf("C Implementation of Integer Binary Tree\n");

    initialize_binary_tree();

    // Build the tree
    insert(1);

    result = search_tree(ROOT,1);

    printf("result = %d\n", result);
    insert(2);
    insert(3);
    insert(4);
    insert(5);
    insert(6);
    insert(7);
    insert(8);
    insert(9);
    insert(10);
    insert(11);
    insert(12);
    insert(13);
    insert(14);
    insert(15);
    insert(16);
    insert(17);
    insert(18);
    insert(19);
    insert(20);
    insert(21);
    insert(22);
    insert(23);
    insert(24);
}