#include <iostream>
#include <queue>
#include <assert.h>

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node(int data): data(data), left(nullptr), right(nullptr)
    {
    };
};


class BinaryTree {
public:
    BinaryTree(): root(nullptr)
    {
    }

    void AddElem( int data )
    {
        if( root == nullptr ) {
            root = new Node(data);
        } else {
            Node* temp = root;
            Node* newNode = new Node(data);
            while( 1 ) {
                if( data <= temp->data ) {
                    if( temp->right == nullptr ) {
                        temp->right = newNode;
                        break;
                    }
                    temp = temp->right;
                } else {
                    if( temp->left == nullptr ) {
                        temp->left = newNode;
                        break;
                    }
                    temp = temp->left;
                }
            }
        }
    }
    ~BinaryTree()
    {
        if( root != nullptr ) {
            std::queue<Node*> queueOfNodes;
            queueOfNodes.push(root);
            while( !queueOfNodes.size() == 0 ) {

                if (queueOfNodes.front()->left != nullptr) {
                    queueOfNodes.push(queueOfNodes.front()->left);
                }
                if (queueOfNodes.front()->right != nullptr) {
                    queueOfNodes.push(queueOfNodes.front()->right);
                }
                delete queueOfNodes.front();
                queueOfNodes.pop();
            }

        }
    }

    void LevelOrder()
    {
        if( root != nullptr ) {
            std::queue<Node*> queueOfNodes;
            queueOfNodes.push(root);
            while( !queueOfNodes.size() == 0 ) {
                if (queueOfNodes.front()->right != nullptr) {
                    queueOfNodes.push(queueOfNodes.front()->right);
                }
                if (queueOfNodes.front()->left != nullptr) {
                    queueOfNodes.push(queueOfNodes.front()->left);
                }
                std::cout << queueOfNodes.front()->data << " ";
                queueOfNodes.pop();
            }

        }
    }
private:
    Node* root;
};

int main() {
    int N = 0;
    BinaryTree tree;
    std::cin >> N;
    assert( N > 0 );
    for( int i = 0; i < N; ++i ) {
        int data{0};
        std::cin >> data;
        tree.AddElem(data);
    }

    tree.LevelOrder();
    return 0;
}