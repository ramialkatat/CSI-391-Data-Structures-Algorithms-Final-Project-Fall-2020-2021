//This code that was written by Rami Katat, is intended to serve as a course project for Data Structures and Algorithms course(CSI 391).

#include <iostream> 
#include <stack> // STL stack
#include<string> //For getline() function
using namespace std;

//Binary Tree
typedef struct TreeNode
{
	char info;
	TreeNode* left, *right;
}
TreeNode;
typedef struct TreeNode* ExpressionTree;


//Prototype functions
//-------------------
// Tree
ExpressionTree Create_Node(int info);
ExpressionTree constructTree(ExpressionTree T, char postfix[]);
int getPriority(char ch);
void Convert_In_To_Post(string infix, char postfix[]);

//Output
void nodeInfo(ExpressionTree T);
void preorder(ExpressionTree T);
void postorder(ExpressionTree T);
void inorder(ExpressionTree T);
void display(ExpressionTree tree, char postfix[]);
void line();

//Input Validation
bool IsExpCorrect(string infix);
bool isOperator(char ch);
bool isOperand(char c);


int main()
{
	cout << "Welcome to the System!" << endl;
	cout << "\nKindly enter an Arithmetic expression using Infix Format: ";
	string infix;
	getline(cin, infix);
	if (!IsExpCorrect(infix)) {
		cout << "Expressions can only contain the following symbols--> [   ( ,  ) ,  + ,  - ,  * ,  / ,  % ,  ^   ] " << endl;
		getline(cin, infix);
	}
	cout << "The entered expression was: " << infix << endl;
	char* postfix = (char*)malloc(sizeof(char) * infix.length());
	Convert_In_To_Post(infix, postfix);
	ExpressionTree tree1 = NULL;
	tree1 = constructTree(tree1, postfix);
	display(tree1, postfix);
	line();
	return 0;
	system("PAUSE");
}

void line()
{
	cout << "=======================================================================\n";
}

void display(ExpressionTree tree, char postfix[])
{
	int choice;
	cout << "\nPlease check the Menu below\n";
	line();
	cout << "1. Traverse the BST in PreOrder(Node, Left, Right).\n";
	cout << "2. Traverse the BST in PostOrder(Left, Right, Node).\n";
	cout << "3. Traverse the BST in InOrder(Left, Node, Right).\n";
	do {
		cout << "\nEnter your choice here (1,2, or 3): ";
		cin >> choice;
		cout << endl;
	} while (choice != 1 && choice != 2 && choice != 3);
	if (choice == 1)
	{
		line();
		cout << "PreOrder Traversal: [ ";
		preorder(tree);
		cout << "]" << endl;
	}
	else if (choice == 2)
	{
		line();
		cout << "PostOrder Traversal: [ ";
		postorder(tree);
		cout << "]" << endl;
	}
	else
	{
		line();
		cout << "InOrder Traversal: [ ";
		inorder(tree);
		cout << "]" << endl;
	}
}

bool isOperand(char ch)
{
	if (ch) //ch in this case can be any character since we are not evaluating.
		return true;
	return false;
}
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^')
		return true;
	return false;
}

bool IsExpCorrect(string infix)
{
	for (unsigned int i = 0; i < infix.length(); i++) {
		if (!isOperand(infix[i]) && !isOperator(infix[i]) && infix[i] != '(' && infix[i] != ')')
			return false;
	}
	return true;
}
// Create a new Tree Node
ExpressionTree Create_Node(int info)
{
	TreeNode* temp;
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL)
	{
		cout << "Out of space!\n";
		return (temp);
	}
	temp->left = NULL;
	temp->right = NULL;
	temp->info = info;
	return temp;
};

ExpressionTree constructTree(ExpressionTree tree, char postfix[])
{
	int i = 0;
	stack<TreeNode*> st;
	TreeNode* temp_tree1;
	TreeNode* temp_tree2;
	while (postfix[i] != '\0')
	{
		if (!(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '%' || postfix[i] == '^'))
		{
			tree = Create_Node(postfix[i]);
			st.push(tree);
		}
		else
		{
			tree = Create_Node(postfix[i]);
			temp_tree1 = st.top();
			st.pop();
			temp_tree2 = st.top();
			st.pop();
			tree->right = temp_tree1;
			tree->left = temp_tree2;
			st.push(tree);
		}
		i++;
	}
	return tree;
}

void nodeInfo(ExpressionTree T)
{
	cout << T->info << " ";
}
void preorder(ExpressionTree T)
{
	if (T != NULL)
	{
		nodeInfo(T);
		preorder(T->left);
		preorder(T->right);
	}
}
void postorder(ExpressionTree T)
{
	if (T != NULL)
	{
		postorder(T->left);
		postorder(T->right);
		nodeInfo(T);
	}
}
void inorder(ExpressionTree T)
{
	if (T != NULL)
	{
		inorder(T->left);
		nodeInfo(T);
		inorder(T->right);
	}
}
int getPriority(char ch)
{
	switch (ch)
	{
	case '^':
		return 4;
	case '%':
		return 3;
	case '/':
	case '*':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}
void Convert_In_To_Post(string infix, char postfix[])
{
	unsigned int counter1 = 0;
	stack<char> st;
	int postCount = 0;
	char element;
	while (counter1 < infix.length())
	{
		element = infix[counter1];
		if (element == '(')
		{
			st.push(element);
			counter1++;
			continue;
		}
		if (element == ')')
		{
			while (!st.empty() && st.top() != '(')
			{
				postfix[postCount++] = st.top();
				st.pop();
			}
			if (!st.empty())
			{
				st.pop();
			}
			counter1++;
			continue;
		}

		if (getPriority(element) == 0)
		{
			postfix[postCount++] = element;
		}
		else
		{
			if (st.empty())
			{
				st.push(element);
			}
			else
			{
				while (!st.empty() && st.top() != '(' && getPriority(element) <= getPriority(st.top()))
				{
					postfix[postCount++] = st.top();
					st.pop();
				}
				st.push(element);
			}
		}
		counter1++;
	}

	while (!st.empty())
	{
		postfix[postCount++] = st.top();
		st.pop();
	}
	postfix[postCount] = '\0';
}