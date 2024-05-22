#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define COUNT 10

//CREAT A STRUCT NODE
typedef struct Course *CoursePointer;
typedef struct Course
{
    char * Course_name;
    int  CreditHours;
    char * CourseCode;
    char * Department;
    char *  Topic[100];
    int NumberOfTopic;
    CoursePointer left;
    CoursePointer right;
    int Height;
};


int COURSESTART = 0;
int COURSEDEPARTMENT = 0;

//function to print the tree in two dimensional
void print2DUtil(CoursePointer root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s\n", root->CourseCode);

    // Process left child
    print2DUtil(root->left, space);
}


//Definition the prototype of function
CoursePointer loadCourses(FILE *courseFile, CoursePointer Tree, char *  department[100]);
CoursePointer InsertCourse(CoursePointer treeNode, CoursePointer Tree);
void FillNodeByUser(CoursePointer node);
CoursePointer Find_using_courseCode( CoursePointer Tree ,char * courseCode);
void printPreOrder(CoursePointer Tree);
int getBalance(CoursePointer N);
CoursePointer FindMin( CoursePointer T );
CoursePointer FindMax( CoursePointer T );
int Height( CoursePointer P );
CoursePointer DoubleRotateWithRight( CoursePointer T1 );
CoursePointer DoubleRotateWithLeft( CoursePointer T3 );
CoursePointer SingleRotateWithRight( CoursePointer T1 );
CoursePointer SingleRotateWithLeft( CoursePointer T2 );
void LexicographicOrder(CoursePointer Tree);
void LexicographicOrderForDepartment(CoursePointer Tree, char * department[100], int numberOfDepartment);
void LexicographicOrderBaseOnDepartment(CoursePointer Tree, char * departmentName);
CoursePointer DeleteNode(CoursePointer root, char * key);
void printNood(CoursePointer Tree);
void saveTree( CoursePointer t, FILE* f);
int Max( int Left, int Right );
CoursePointer DeleteFirstChar(CoursePointer Tree ,char c);
void FindBaseOnDepartment(CoursePointer Tree ,char * department, char * courseCodes[50]);
void FindBaseOnCharachter(CoursePointer Tree ,char * c, char * courseCodes[50]);
int Find=0;
int Delete=0;

int main() {
    //the information  in the file loaded by default to make user make oparation on it
    printf("Please enter the number from the menu: \n");
    printf("1- Read the file courses.txt file and create the tree. \n");
    printf("2- Insert a new course from the user with all its associated data.\n");
    printf("3- Find a course and support updating of its information. \n");
    printf("4- List courses in lexicographic order with their associated information (credit hours, IDs, and topics). \n");
    printf("5- List all topics associated with a given course. \n");
    printf("6- List all courses in lexicographic order that belong to the same department.\n");
    printf("7- Delete a course\n");
    printf("8- Delete all courses that start with a specific letter\n");
    printf("9- Delete all courses belong to a given department.\n");
    printf("10- Save all words in file offered_courses.txt \n");
    //define a file
    FILE *courseFile;
    int choice;
    int save = 0;
    char *  departments[100];
    int numberOfDepartment = 0;
    //create a null tree to insert data on it
    CoursePointer Tree = NULL;
    char line[500];
    int flagOptionUserUpdate = 0;
    //open file
    courseFile = fopen("courses.txt", "r");
    //check if the file is null or not
    if (courseFile == NULL) {
        printf("File does not exist!!!\n");
        return -1;
    }
    //loop to count the number of department
    while (fgets(line, 500, courseFile)) {
        numberOfDepartment++;
    }
    //call the function how read file and load data in avl tree
    Tree = loadCourses(courseFile, Tree, departments);
    //call function that print avl tree in two dimensional
    print2DUtil(Tree, 0);
    fclose(courseFile);
    while(1){
        printf("\nEnter your choice");
        scanf("%d", &choice);

        //insert new course
        if(choice == 2){
            CoursePointer treeNodeAdded = malloc(sizeof(struct Course));
            printf("Enter a course code\n");
            treeNodeAdded->CourseCode = malloc(256);
            scanf("%s", treeNodeAdded->CourseCode);
            FillNodeByUser(treeNodeAdded);
            Tree = InsertCourse(treeNodeAdded, Tree);
            printf("The new course you added \n");
            printNood(treeNodeAdded);
        }
        print2DUtil(Tree,0);

        //Find and Update Course
        if(choice == 3)
        {


            char * courseCodeUpdated;
            printf("Enter a course code :\n");
            courseCodeUpdated = malloc(256);
            scanf("%s", courseCodeUpdated);
            CoursePointer treeNodeUpdated = Find_using_courseCode(Tree, courseCodeUpdated);
            if(treeNodeUpdated == NULL)
                continue;
            printf("\n The information about the course you want to update on \n");
            printNood(treeNodeUpdated);
            printf("If you want to update in data enter 1 \n");
            scanf("%d",&flagOptionUserUpdate);
            if(flagOptionUserUpdate == 1) {
                FillNodeByUser(treeNodeUpdated);
                printf("The data you entered are :");
                printNood(treeNodeUpdated);
                flagOptionUserUpdate = 0;
            }
        }
        //list tree in Lexicographic Order
        if(choice == 4)
        {
            LexicographicOrder(Tree);
        }
        //print the topics for course
        if(choice == 5)
        {
            printf("Enter a course code");
            char * courseCodeentered = malloc(256);
            scanf("%s", courseCodeentered);
            CoursePointer treeNodeListTopics = Find_using_courseCode(Tree ,courseCodeentered);
            if(treeNodeListTopics == NULL)
                continue;
            printf("Tobics : \n");
            for (int i = 0; i < treeNodeListTopics->NumberOfTopic; i++) {
                printf("%s , ", treeNodeListTopics->Topic[i]);
            }
        }
        //list tree in Lexicographic Order
        if(choice == 6)
        {
            LexicographicOrderForDepartment(Tree, departments, numberOfDepartment);
        }
        //delete course
        if(choice == 7)
        {
            char * courseDelete = malloc(256);
            printf("Enter the course you want to delete");
            scanf("%s", courseDelete);
            Tree = DeleteNode(Tree, courseDelete);
            print2DUtil(Tree, 0);
        }
        //delete course start with specific letter
        if(choice == 8)
        {
            char * names[50];
            char * ch;
            ch = malloc(256);
            printf("Enter the character start with course name you want to delete: \n");
            scanf("%s", ch);
            FindBaseOnCharachter(Tree, ch, names);
            for(int i=0; i < COURSESTART; i++)
            {
               Tree = DeleteNode(Tree, names[i]);
            }
            print2DUtil(Tree, 0);
        }
        //delete course that have the same department which was entered by user
        if (choice==9)
        {
            char * names[50];
            char * departmentName;
            departmentName = malloc(256);
            printf("Enter the department name you want to delete its courses: \n");
            scanf("%s", departmentName);
            FindBaseOnDepartment(Tree, departmentName, names);
            for(int i=0; i < COURSEDEPARTMENT; i++)
            {
               Tree = DeleteNode(Tree, names[i]);
            }
            print2DUtil(Tree, 0);
        }
        //load data in new file
        if (choice == 10)
        {
            FILE *f;
            f = fopen(" offered_courses.txt", "w");
            saveTree(Tree, f);
            fclose(f);
            save=1;
            printf("THE NEW DATA IS NOW UPDATED\n\n");
        }

    }
    return 0;
}

//open file and read data from it and store it in avl tree
CoursePointer loadCourses(FILE *courseFile, CoursePointer Tree, char *  department[100]){
    printf("Load the Course information file\n");
    int flag = 1, i=0, iDep = 0;
    char line[500];
    CoursePointer treeNode;
    char * token;
    courseFile = fopen("courses.txt", "r");
    while (fgets(line, 500, courseFile)) {
        token = strtok(line, ":");
        treeNode = malloc( sizeof( struct Course ) );
        treeNode->Height = 0;
        treeNode->left = treeNode->right = NULL;
        while (token != NULL) {
            switch (flag) {
                case 1:
                    treeNode->Course_name = malloc(sizeof(token) * 2);
                    strcpy(treeNode->Course_name, token);
                    token = strtok(NULL, "#");
                    flag++;
                    break;
                case 2:
                    treeNode->CreditHours =  atoi(token);
                    token = strtok(NULL, "#");
                    flag++;
                    break;
                case 3:
                    treeNode->CourseCode = malloc(sizeof(token) * 2);
                    strcpy(treeNode->CourseCode, token);
                    token = strtok(NULL, "/");
                    flag++;
                    break;
                case 4:
                    treeNode->Department = malloc(sizeof(token) * 2);
                    strcpy(treeNode->Department, token);
                    department[iDep] = malloc(sizeof(token) * 2);
                    strcpy( department[iDep], token);
                    iDep++;
                    token = strtok(NULL, ",");
                    flag++;
                    break;
                case 5:
                    while (token != NULL) {
                        treeNode->Topic[i] = malloc(sizeof(token)*2);
                        strcpy(treeNode->Topic[i], token);
                        token = strtok(NULL, ",");
                        i++;
                    }
                    treeNode->NumberOfTopic = i;
            }
        }
        Tree = InsertCourse(treeNode, Tree);
        flag = 1;
        i=0;
    }
    fclose(courseFile);
    return Tree;
}

//insert data in avl tree
CoursePointer InsertCourse(CoursePointer treeNode, CoursePointer Tree)
{
    if( Tree == NULL )
    {
        Tree = treeNode;
    }

    else if( strcasecmp(treeNode->CourseCode,Tree->CourseCode) < 0  )
    {
        Tree->left = InsertCourse(treeNode, Tree->left );
        if( Height( Tree->left ) - Height( Tree->right ) == 2 )
            if( strcasecmp(treeNode->CourseCode,Tree->left->CourseCode) < 0 )
                Tree = SingleRotateWithLeft( Tree );
            else
                Tree = DoubleRotateWithLeft( Tree );
    }

    else if( strcasecmp(treeNode->CourseCode,Tree->CourseCode) > 0 )
    {
        Tree->right = InsertCourse(treeNode ,Tree->right);
        if( Height( Tree->right ) - Height( Tree->left ) == 2 )
            if( strcasecmp(treeNode->CourseCode, Tree->right->CourseCode) > 0 )
                Tree = SingleRotateWithRight( Tree );
            else
                Tree = DoubleRotateWithRight( Tree );
    }
// update the Height of tree
    Tree->Height = Max( Height( Tree->left ), Height( Tree->right ) ) + 1;
    return Tree;
}

//this function will get the balance to this node to chick if it balance or not
int getBalance(CoursePointer N)
{
    if (N == NULL)
        return 0;
    else
        return Height(N->left) - Height(N->right);
}

// this function will find the minimum node in the tree
CoursePointer FindMin( CoursePointer T )
{
    if( T == NULL )
        return NULL;
    else if( T->left == NULL )
        return T;
    else
        return FindMin( T->left );
}

// this function will find the maximum node in the tree
CoursePointer FindMax( CoursePointer T )
{
    if( T != NULL )
        while( T->right != NULL )
            T = T->right;

    return T;
}

// this function will find the Height of the tree
int Height( CoursePointer P )
{
// this function will find the max between two number(Hight of left and right part of tree)
    if( P == NULL )
        return -1;
    else
        return P->Height;
}
//find the max
int Max( int Left, int Right )
{
    if(Left>Right)
        return Left;
    else
        return Right;
}

// this function will Rotate the node With Left Single Rotate
CoursePointer SingleRotateWithLeft( CoursePointer T2 )
{


    CoursePointer T1 = T2->left;
    T2->left = T1->right;
    T1->right = T2;

    T2->Height = Max( Height( T2->left ), Height( T2->right ) ) + 1;
    T1->Height = Max( Height( T1->left ), T2->Height ) + 1;

    return T1;
}

// this function will Rotate the node With Right Single Rotate
CoursePointer SingleRotateWithRight( CoursePointer T1 )
{
    CoursePointer T2 = T1->right;
    T1->right = T2->left;
    T2->left = T1;

    T1->Height = Max( Height( T1->left ), Height( T1->right ) ) + 1;
    T2->Height = Max( Height( T2->right ), T1->Height ) + 1;

    return T2;
}

// this function will Rotate the node With left double Rotate
CoursePointer DoubleRotateWithLeft( CoursePointer T3 )
{

    T3->left = SingleRotateWithRight( T3->left );


    return SingleRotateWithLeft( T3 );
}

// this function will insert (add) the book in  tree
CoursePointer DoubleRotateWithRight( CoursePointer T1 )
{

    T1->right = SingleRotateWithLeft( T1->right );


    return SingleRotateWithRight( T1 );
}

CoursePointer Find_using_courseCode(CoursePointer Tree ,char * courseCode)
{
    if( Tree == NULL )
    {
        printf(" Not Exist in tree");
        return NULL;
    }
    if( strcasecmp(courseCode ,Tree->CourseCode) < 0 )
        return Find_using_courseCode(  Tree->left, courseCode);
    else if(strcasecmp(courseCode, Tree->CourseCode) > 0 )
        return Find_using_courseCode( Tree->right, courseCode);
    else if (strcmp(courseCode, Tree->CourseCode) == 0)
    {
        return Tree;
    }
    else
    {
    printf(" Not Exist in tree");
    return NULL;
    }
}
void FillNodeByUser(CoursePointer node){
    int i = 0;
    printf("Enter the course name\n");
    node->Course_name = malloc(256);
    scanf("%s", node->Course_name);

    printf("Enter the number of credit hour\n");
    scanf("%d",&node->CreditHours);

    printf("Enter the name of department\n");
    node->Department = malloc(256);
    scanf("%s", node->Department);

    printf("Enter the number of Tobics\n");
    scanf("%d",&node->NumberOfTopic);

    printf("Enter the topics\n");
    for (i = 0; i < node->NumberOfTopic; i++) {
        node->Topic[i] = malloc(256);
        scanf("%s", node->Topic[i]);
    }
}
// Print the tree
void printPreOrder(CoursePointer Tree) {
    if (Tree != NULL) {
        printf("\nCourse \n");
        printf("Course Name is : %s \n", Tree->Course_name);
        printf("Course Code is : %s \n", Tree->CourseCode);
        printf("Course Department is : %s \n", Tree->Department);
        printf("Credit Hours is : %d \n", Tree->CreditHours);
        printf("Topics : \n");
        for (int i = 0; i < Tree->NumberOfTopic; i++) {
                printf("%s , ", Tree->Topic[i]);
        }
        printPreOrder(Tree->left);
        printPreOrder(Tree->right);
    }
}

//print the information about node
void printNood(CoursePointer Tree) {
    if (Tree == NULL)
      return ;
  printf("Course Name is : %s \n", Tree->Course_name);
  printf("Course Code is : %s \n", Tree->CourseCode);
  printf("Course Department is : %s \n", Tree->Department);
  printf("Credit Hours is : %d \n", Tree->CreditHours);
  printf("Topics : \n");
  for (int i = 0; i < Tree->NumberOfTopic; i++) {
          printf("%s , ", Tree->Topic[i]);
  }
}

//print the information that ordered by lexicographic
void LexicographicOrder(CoursePointer Tree)
{
    if (Tree == NULL)
      return ;
   LexicographicOrder(Tree->left);
   printf("\nCourse \n");
   printf("Credit Hours is : %d \n", Tree->CreditHours);
   printf("Course Code is : %s \n", Tree->CourseCode);
   printf("Topics : \n");
   for (int i = 0; i < Tree->NumberOfTopic; i++) {
       printf("%s , ", Tree->Topic[i]);
   }
   LexicographicOrder(Tree->right);


}
//order by lexicographic for dapartment
void LexicographicOrderForDepartment(CoursePointer Tree, char * department[100], int numberOfDepartment)
{
    for(int i=0; i< numberOfDepartment; i++){
        printf("\nFor Department %s \n Courses is : \n", department[i]);
        LexicographicOrderBaseOnDepartment(Tree ,department[i]);
    }
}

void LexicographicOrderBaseOnDepartment(CoursePointer Tree, char * departmentName)
{
  if (Tree == NULL)
      return ;
   LexicographicOrderBaseOnDepartment(Tree->left, departmentName);
   if (strcmp(departmentName, Tree->Department) == 0){
   printf("\nCourse \n");
   printf("Credit Hours is : %d \n", Tree->CreditHours);
   printf("Course Code is : %s \n", Tree->CourseCode);
   printf("Topics : \n");
   for (int i = 0; i < Tree->NumberOfTopic; i++) {
       printf("%s , ", Tree->Topic[i]);
   }
   }
   LexicographicOrderBaseOnDepartment(Tree->right, departmentName);
}

//delete node in avl tree
CoursePointer DeleteNode(CoursePointer root, char * key)
{
    if (root == NULL)
        return root;
// Checks if there is a match between the name of the book the user entered and the name of the books in the tree for deletion
    if (strcasecmp (key,root->CourseCode)<0 )
        root->left = DeleteNode(root->left, key);


    if (strcasecmp (key,root->CourseCode)>0 )
        root->right = DeleteNode(root->right, key);

    else if (strcasecmp(key,root->CourseCode)==0)
    {

        if( (root->left == NULL) || (root->right == NULL) )
        {
            CoursePointer temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }

            free(temp);
            Delete=1;
        }
        else
        {

            CoursePointer temp = FindMin(root->right);

            // Copy the in order successor's data to this node
            strcpy(root->CourseCode,temp->CourseCode);

            // Delete the in order successor
            root->right = DeleteNode(root->right, temp->CourseCode);
        }
    }
    // If the tree had only one node then return
    if (root==NULL)
        return root;

    // update hight of  new node
    root->Height = 1 + Max(Height(root->left), Height(root->right));
//get the balance to this node to chick if it balance or not
    int balance = getBalance(root);

    // If this node unbalanced, then

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return SingleRotateWithRight(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = SingleRotateWithLeft(root->left);
        return SingleRotateWithRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return SingleRotateWithLeft(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = SingleRotateWithRight(root->right);
        return SingleRotateWithLeft(root);
    }

    return root;
}

//delete node that start with specific letter
CoursePointer DeleteFirstChar(CoursePointer Tree ,char c)
{
    if( Tree == NULL )
    {
        printf(" Not Exist in tree");
        return NULL;
    }
     if(strncmp(Tree->Course_name, c, 1) == 0)
         Tree = DeleteNode(Tree, Tree->Course_name);
    return Find_using_courseCode(  Tree->left, c);
    return Find_using_courseCode( Tree->right, c);
}

//search for nodes that starts with same letter
void FindBaseOnCharachter(CoursePointer Tree ,char * c, char * courseCodes[50])
{
    if( Tree == NULL )
        return NULL;

    if(strncmp(Tree->Course_name, c, 1) == 0)
    {
        courseCodes[COURSESTART] = Tree->CourseCode;
        COURSESTART++;
    }
    FindBaseOnCharachter(  Tree->left, c , courseCodes);
    FindBaseOnCharachter( Tree->right, c , courseCodes);
}

void FindBaseOnDepartment(CoursePointer Tree ,char * department, char * courseCodes[50])
{
    if( Tree == NULL )
        return NULL;

    if(strcmp(Tree->Department, department) == 0)
    {
        courseCodes[COURSEDEPARTMENT] = Tree->CourseCode;
        COURSEDEPARTMENT++;
    }
    FindBaseOnDepartment(  Tree->left, department , courseCodes);
    FindBaseOnDepartment( Tree->right, department , courseCodes);
}

//save tree in file
void saveTree(CoursePointer t, FILE* f)
{
    if( t != NULL)
    {
        saveTree( t->left, f );
        fprintf(f,"%s:%s#%d#%s/", t->Course_name, t->CourseCode, t->CreditHours, t->Department);
        for (int i = 0; i < t->NumberOfTopic; i++) {
            fprintf(f,"%s,", t->Topic[i]);
        }
        fprintf(f,"\n");
        saveTree( t->right, f);
    }
}
