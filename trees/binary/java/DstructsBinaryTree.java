import java.util.LinkedList;
import java.util.Queue;
import java.lang.Math;
import java.util.Random;
import java.lang.Thread;

/**
 * DstructsBinaryTree.java
 * 
 * A binary tree data structure implmentation
 */

// ------------------------------------------------------------------------------------------------
// The tree node object
class BinaryTreeNode {

    int value;
    int level;
    BinaryTreeNode left;
    BinaryTreeNode right;
    BinaryTreeNode parent;

    public BinaryTreeNode(int value) {
        this.value  = value;
        this.left   = null;
        this.right  = null;
        this.parent = null;
        this.level  = -99;
    }

}

// ------------------------------------------------------------------------------------------------
public class DstructsBinaryTree {

    BinaryTreeNode root = null;

    // A multi-purpose FIFO node queue
    Queue<BinaryTreeNode> nodeQueue = new LinkedList<BinaryTreeNode>();

    // --------------------------------------------------------------------------------------------
    // Add a node to the first available node 
    public BinaryTreeNode addNode(int value) {

        BinaryTreeNode node = new BinaryTreeNode(value);

        // If root is null then we have an empty tree.  Set value as root
        if (this.root == null) {
            this.root   = node;
            node.level  = 1;
            node.parent = null;
        
        // Otherwise, add the node in first available slot
        } else {
            insert(this.root, node);
        }

        return node;
    }

    // --------------------------------------------------------------------------------------------
    // Return the current root of the tree
    public BinaryTreeNode getRoot() {
        return this.root;
    }

    // --------------------------------------------------------------------------------------------
    // Get the maximum number of levels in this tree.  This is done by finding the bottom most 
    // node and extracting its level paramater
    public int getMaxLevels() {

        BinaryTreeNode node;

        if (getRoot() == null) {
            System.out.println("getMaxLevels: Tree is empty, no levels to report");
            return -99;
        }

        node = findDeepestNode(getRoot());

        return node.level;

    }

    // --------------------------------------------------------------------------------------------
    // Check if a node is full.  This means its left and right children are not null
    private boolean nodeFull(BinaryTreeNode node) {
        if (node.left != null && node.right != null) {
            return true;
        }
        return false;
    }

    // --------------------------------------------------------------------------------------------
    // Place the node in first available location at each level
    private void insert(BinaryTreeNode node, BinaryTreeNode newNode) {

        // Check if the node has an available child slot
        if (node.left == null) {
            newNode.level  = node.level + 1;
            newNode.parent = node;
            node.left      = newNode;
            nodeQueue.clear();
            System.out.println("INSERTING NODE: " + newNode.value);
        } else if (node.right == null) {
            newNode.level  = node.level + 1;
            newNode.parent = node;
            node.right     = newNode;
            nodeQueue.clear();
            System.out.println("INSERTING NODE: " + newNode.value);
        
        // Otherwise, node is full
        } else {
            nodeQueue.add(node.left);
            nodeQueue.add(node.right);

            insert(nodeQueue.remove(), newNode);
        }

    }

    // --------------------------------------------------------------------------------------------
    // Find a node for a given value.  If node doesn't exist then return null
    public BinaryTreeNode findNode(BinaryTreeNode node, int value) {

        // Check if this node matches
        if (node.value == value) {
            return node;
        }

        // Otherwise, add the node's children to node queue and move to next node
        if (node.left != null) {
            nodeQueue.add(node.left);
        }
        if (node.right != null) {
            nodeQueue.add(node.right);
        }

        // If queue is empty then the node does not exist
        if (nodeQueue.isEmpty()) {
            return null;
        }

        return findNode(nodeQueue.remove(), value);
    }

    // --------------------------------------------------------------------------------------------
    // Find deepest node in the tree
    public BinaryTreeNode findDeepestNode(BinaryTreeNode node) {

        if (node.left != null) {
            nodeQueue.add(node.left);
        }

        if (node.right != null) {
            nodeQueue.add(node.right);
        }

        // If nothing else is left in the queue then we currently have the deepest node
        if (nodeQueue.isEmpty()) {
            return node;
        }

        return findDeepestNode(nodeQueue.remove());

    }

    // --------------------------------------------------------------------------------------------
    // Find the number of nodes per level
    public int numNodesInLevel(int level) {

        BinaryTreeNode node = getRoot();

        // Create a temporary queue to hold nodes =
        Queue<BinaryTreeNode> queue = new LinkedList<>();

        int cnt = 0;

        if (node == null) {
            System.out.println("numNodesInLevel: Tree is empty, no levels to report");
            return 0;
        }

        // Clear out the queue
        queue.clear();

        // Start at the root and work down to the desired level
        queue.add(node);

        // Recursively traverse the tree to get the value
        cnt = findNumNodesInLevel(queue, level, cnt);

        return cnt;

    }

    // --------------------------------------------------------------------------------------------
    // Recursive function which finds the number of nodes for desired level
    private int findNumNodesInLevel(Queue<BinaryTreeNode> queue, int level, int counter) {

        BinaryTreeNode node;       
        
        if (queue.isEmpty()) {
            return counter;
        }

        node = queue.remove();

        if (node.level == level) {
            counter++;
        } else if (node.level < level) {
            if (node.left != null) {
                queue.add(node.left);
            }
            if (node.right != null) {
                queue.add(node.right);
            }
        } else {
            return counter;
        }

        return findNumNodesInLevel(queue, level, counter);

    }

    // --------------------------------------------------------------------------------------------
    // Remove a node.  Once a node is removed it is replaced with the bottom, right most node.
    public void remove(int value) {

        // Find the node associated with the value
        BinaryTreeNode node1 = findNode(this.root, value); // Node to delete
        BinaryTreeNode node2 = findDeepestNode(getRoot()); // Node at bottom of tree to replace deleted node

        // If node doesn't exist then error out
        if (node1 == null) {
            System.out.println("!! ERROR !! Node: " + value + " does not exist!");
            return;
        }

        // If node1 is the same as node2 then we are deleting the bottom most node
        if (node1 == node2) {
            if (node1.parent == null) {
                this.root = null;
                node1     = null;
                return;
            } 

            if (node1.parent.left == node1) {
                node1.parent.left = null;
            } else if (node1.parent.right == node1) {
                node1.parent.right = null;
            }

            node1 = null;
            return;
        }

        //
        // Replace node 1 with node 2, reassigning all linkages
        //

        // Remove linkage for the node we are going to move
        if (node2.parent.left == node2) {
            node2.parent.left = null;
        } else if (node2.parent.right == node2) {
            node2.parent.right = null;
        }

        // Reassing parent and children of removed node to the node replacing it
        if (node1 == this.root) {
            node2.parent = null;
            this.root    = node2;
        } else {
            node2.parent = node1.parent;
        }

        // Assign node1 parent connection to the node replacing it
        if (node1.parent != null) {
            if (node1.parent.left == node1) {
                node1.parent.left = node2;
            } else if (node1.parent.right == node1) {
                node1.parent.right = node2;
            }
        }

        // Assign node1 children connections to node replacing it
        node2.left  = node1.left;
        node2.right = node1.right;

        // Update the node level
        node2.level = node1.level;

        // Change the parent node of the children to point to new node
        if (node2.left != null) {
            node2.left.parent = node2;
        }
        if (node2.right != null) {
            node2.right.parent = node2;
        }

        // Set the deleted node to Null (get it ready for garbage collection)
        node1 = null;

        return;

    }

    // --------------------------------------------------------------------------------------------
    // Print the tree with node leader lines to easily view contents of current Binary Tre
    public void printTree(int numChars)  {

        // Variables needed to construct tree and report tree statistics
        BinaryTreeNode node;
        int level;
        int numSpaces; 
        int maxChars;
        int maxNodes;
        int numLevels;
        int numNodesInLevel;
        int offset;

        // Leader line variables
        int leaderLength;
        int centerUp=0;
        int centerDn;

        // Store each level's offsets and spacing into arrays for easy access
        int[] levelOffset;
        int[] levelLeaderLength;
        int[] levelLeaderDnOffset;
        int[] levelLeaderUpOffset;

        // To keep the tree symmetric we must ensure that the number of characters are odd
        if (numChars % 2 == 0) {
            numChars++;
        }

        // Set the minimum number of spaces between nodes to match the number of characters per node
        numSpaces = numChars;

        // Set the string format.  The value printed will be converted to a String.
        String autoFormat = "%" + numChars + "s";

        // Get the number of levels in this tree
        numLevels = getMaxLevels();

        if (numLevels == -99) {
            System.out.println("Tree is empty!");
            return;
        }

        // Initialize storage arrays
        levelOffset         = new int[numLevels];
        levelLeaderLength   = new int[numLevels];
        levelLeaderDnOffset = new int[numLevels];
        levelLeaderUpOffset = new int[numLevels];

        // Calculate the maximum number of nodes in a single level (this is the deepest level)
        maxNodes = (int) Math.pow(2, numLevels-1);

        // Calculate the maximum number of characters a single line will need
        maxChars = maxNodes*numChars + (maxNodes-1)*numSpaces + 1;        

        for (int i=0; i<numLevels; i++) {

            // Max number of possible nodes in level
            numNodesInLevel = (int) Math.pow(2, i);

            // Calculate the offset between nodes and spaces
            offset = maxChars - numNodesInLevel*numChars - (numNodesInLevel-1)*numSpaces;
            offset = (int) Math.ceil((offset / (numNodesInLevel*2)));

            // Calculate leader line dimensions
            if (i > 0) {
                centerDn = centerUp;
            } else {
                centerDn = 0;
            }

            centerUp = offset + (numChars/2);

            if (i > 0) {
                leaderLength = centerDn - centerUp - 1;
            } else {
                leaderLength = 0;
            }

            levelOffset[i] = offset;
            levelLeaderDnOffset[i] = centerDn;
            levelLeaderUpOffset[i] = centerUp;
            levelLeaderLength[i]   = leaderLength;

        }

        // Clear the node queue
        nodeQueue.clear();
        nodeQueue.add(this.root);
        level = 0;

        while(nodeQueue.size() > 0) {
            
            node = nodeQueue.remove();                        

            if (node.level != level) {
                level++;
                System.out.println("");

                // Print leader lines
                if (level > 1) {
                    numNodesInLevel = (int) Math.pow(2, level-2);

                    for (int i=0; i<numNodesInLevel; i++) {
                        for (int j=0; j<levelLeaderUpOffset[level-1]; j++) {
                            System.out.printf(" ");
                        }
                        System.out.printf("+");
                        for (int j=0; j<levelLeaderLength[level-1]; j++) {
                            System.out.printf("-");
                        }
                        System.out.printf("+");
                        for (int j=0; j<levelLeaderLength[level-1]; j++) {
                            System.out.printf("-");
                        }
                        System.out.printf("+");
                        for (int j=0; j<levelLeaderUpOffset[level-1]; j++) {
                            System.out.printf(" ");
                        }
                        for (int j=0; j<numSpaces; j++) {
                            System.out.printf(" ");
                        }
                    }
                }
                System.out.println("");
            }

            for (int i=0; i<levelOffset[level-1]; i++) {
                System.out.printf(" ");
            }
            System.out.printf("" + autoFormat + "", String.valueOf(node.value));
            for (int i=0; i<levelOffset[level-1]; i++) {
                System.out.printf(" ");
            }
            for (int i=0; i<numSpaces; i++) {
                System.out.printf(" ");
            }

            // Add the nodes linked to the current node
            if (node.left != null) {
                nodeQueue.add(node.left);
            }

            if (node.right != null) {
                nodeQueue.add(node.right);
            }

        }

        System.out.println("");
        System.out.println("");
    }

    // --------------------------------------------------------------------------------------------
    // Print each node details
    public void printNodeDetails()  {
        BinaryTreeNode node;
        BinaryTreeNode left;
        BinaryTreeNode right;
        BinaryTreeNode parent;

        // Clear the node queue
        nodeQueue.clear();
        nodeQueue.add(this.root);

        while(nodeQueue.size() > 0) {
            
            node   = nodeQueue.remove();

            if (node == null) {
                System.out.println("printNodeDetails(): Tree is empty, no node information");
                return;
            }

            left   = node.left;
            right  = node.right;
            parent = node.parent;
            
            System.out.printf("NODE: %7d -- ", node.value);

            if (parent == null) {
                System.out.printf("Parent:    NULL, ");
            } else {
                System.out.printf("Parent: %7d, ", parent.value);
            }

            if (left == null) {
                System.out.printf("Left:    NULL, ");
            } else {
                System.out.printf("Left: %7d, ", left.value);
            }

            if (right == null) {
                System.out.printf("Right:    NULL, ");
            } else {
                System.out.printf("Right: %7d, ", right.value);
            }

            System.out.printf("Level: %4d\n", node.level);

            // Add the nodes linked to the current node
            if (node.left != null) {
                nodeQueue.add(node.left);
            }

            if (node.right != null) {
                nodeQueue.add(node.right);
            }
        }
    }

    public static void main(String[] args) {
        DstructsBinaryTree tree = new DstructsBinaryTree();
        // tree.addNode(1);
        // tree.addNode(2);
        // tree.addNode(3);
        // tree.addNode(4);
        // tree.addNode(5);
        // tree.addNode(6);
        // tree.addNode(7);
        // tree.addNode(8);
        // tree.addNode(9);
        // tree.addNode(10);
        // tree.addNode(11);
        // tree.addNode(12);
        // tree.addNode(13);
        // tree.addNode(14);
        // tree.addNode(15);
        // tree.addNode(16);
        // tree.addNode(17);
        // tree.addNode(18);
        // tree.addNode(19);
        // tree.addNode(20);
        // tree.printTree(4);
        // BinaryTreeNode node = tree.findDeepestNode(tree.getRoot());
        // if (node == null) {
        //     System.out.println("UH OH!  No node");
        // } else {
        //     System.out.println("Deepest node is " + node.value);
        // }        
        // System.out.println("*** Remove Node 20");
        // tree.remove(20);
        // tree.printTree(4);
        // System.out.println("*** Remove Node 19");
        // tree.remove(19);
        // tree.printTree(4);
        // System.out.println("*** Remove Node 8");
        // tree.remove(8);
        // tree.printTree(4);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 5");
        // tree.remove(5);
        // tree.printTree(4);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 1");
        // tree.remove(1);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 3");
        // tree.remove(3);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 11");
        // tree.remove(11);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Add Node 10000");
        // tree.addNode(10000);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 2");
        // tree.remove(2);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 16");
        // tree.remove(16);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 10000");
        // tree.remove(10000);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 17");
        // tree.remove(17);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 15");
        // tree.remove(15);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 7");
        // tree.remove(7);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 12");
        // tree.remove(12);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 18");
        // tree.remove(18);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 6");
        // tree.remove(6);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 4");
        // tree.remove(4);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 13");
        // tree.remove(13);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 14");
        // tree.remove(14);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 9");
        // tree.remove(9);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Remove Node 10");
        // tree.remove(10);
        // tree.printTree(5);
        // tree.printNodeDetails();
        // System.out.println("*** Add Node 10000");
        // tree.addNode(10000);
        // tree.printTree(5);
        // tree.printNodeDetails();

        while (true) {
            System.out.println("Howdy");
            try {
                Thread.sleep(1000);
            } catch (Exception e) {
                System.out.println(e);
            }
        }


    }
}
