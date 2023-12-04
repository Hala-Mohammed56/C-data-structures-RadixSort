/// Name : Hala Mohammed
/// ID : 1210312
/// Section : 3 - Saadeddin Hroub

/**The program is made to use Radix Sort to arrange and sort a list of strings
  inside of a menu-driven application.
  To handle strings read from an input file,
  it makes use of a doubly linked list.
  The menu include the ability to load strings,
  print strings that have been sorted and those that haven't,
  add and remove words, save to an output file,
  and provide an exit option. **/

/// includes several libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



///the definition of the struct
struct Node {
    char Data[31];// declares a character array with a size of 31
    struct Node* Next;// declares a pointer to point to the next node in the LL
    struct Node* Prev;// declares a pointer to point to the prev node in the LL
};



///prototype for the functions
int IsEmpty(struct Node* L);
struct Node* MakeEmpty(struct Node* L);
void Delete(struct Node* L, const char* word);
void Delete_Word(struct Node* list);
void Insert(const char* word, struct Node* L);
void printList(struct Node* L);
void DeleteList(struct Node* L);
int size(struct Node* L);
int FindMaxLength(struct Node* L);
void addSpace(struct Node* L);
void RadixSort(struct Node* L);
void Load_the_strings(struct Node* list);
void Print_Sorted_Strings(struct Node* list);
void Save_To_File(struct Node* list);
void Add_New_Word(struct Node* list);
void View_Menu();
int The_Choice();
void Menu_Choice(struct Node* list, int choice);



///the main() function
int main() {
    struct Node* list = MakeEmpty(NULL); //creating an empty linked list
    //infinite loop
    while (1) {
        View_Menu();// Display the menu
        int choice = The_Choice();//get the choice from user
        Menu_Choice(list, choice);
    }

    return 0;
}



///Checks if the list is empty
int IsEmpty(struct Node* L) {
    return L->Next == NULL && L->Prev == NULL;
}



///Creates a Linked List
struct Node* MakeEmpty(struct Node* L) {
    if (L != NULL)// checks if the L is not NULL ( There is a LL )
        DeleteList(L); // delete the list


    L = (struct Node*)malloc(sizeof(struct Node));// allocates memory for a new node using the malloc

    if (L == NULL) { // checking if there is an enough memory available to create the new node
        printf("Out of memory!\n");
        return NULL;
    }

   //sets the next and prev pointers to NULL of new node
    L->Next = NULL;
    L->Prev = NULL;


    return L;// return L ( points to the newly created node)
}



/// deletes the word from the LL
void Delete(struct Node* L, const char* Dword) {


    // Handle empty list
    if (L == NULL || L->Next == NULL) {
        printf("The List is empty !\n");
        return;
    }

    // Search for the node with the word to delete
    struct Node* currentL = L->Next;
    while (currentL != NULL && strcmp(currentL->Data, Dword) != 0) {
        currentL = currentL->Next;
    }

    // Handle case where word is not found
    if (currentL == NULL) {
        printf("Word not found in the list.\n");
        return;
    }

    // If word is found, delete the node
    if (strcasecmp(currentL->Data, Dword) == 0) {
        // Update the previous node's next pointer
        if (currentL->Prev != NULL) {
            currentL->Prev->Next = currentL->Next;
        }

        // Update the next node's previous pointer
        if (currentL->Next != NULL) {
            currentL->Next->Prev = currentL->Prev;
        }

        // If the node to delete is the first node in LL update the pointer
        if (L->Next == currentL) {
            L->Next = currentL->Next;

            // Update the new first node's previous pointer
            if (currentL->Next != NULL) {
                currentL->Next->Prev = NULL;
            }
        }

        // Free the memory of the node you want to delete
        free(currentL);
        printf("Word was deleted !\n");
    }

    else {
        printf("Word not found ! \n");
         }
}



///function to Delete Word
void Delete_Word(struct Node* L) {
    // store the word to be deleted
    char Dword[31];

    printf("Enter the word you want to delete : ");
    scanf("%30s", Dword); // Read the input word from the user, limiting it to 30 characters

    // Find the maximum length of the Strings in the LL
    int maxLen = FindMaxLength(L);

    // Calculate the number of spaces
    int numSpaces = maxLen - strlen(Dword);

    // Add spaces to the entered word
    for (int x = 0; x < numSpaces; x++) {
        strncat(Dword, " ", sizeof(Dword) - strlen(Dword) - 1);
    }

    // Print the list before deletion
    printf("List before delete the word:\n");
    printList(L);

    // Delete the word from the LL
    Delete(L, Dword);

    // Print the list after deletion
    printf("List after delete the word :\n");
    printList(L);
}





/// creates a new node to insert the "Data" in LL
void Insert(const char* Iword, struct Node* L) {
    // Allocate memory for a new Node
    struct Node* newN = (struct Node*)malloc(sizeof(struct Node));

    // Initialize the Node
    newN->Next = NULL;
    newN->Prev = NULL;

    // Copy the strings into new node (Data)
    strncpy(newN->Data, Iword, sizeof(newN->Data) - 1);
    newN->Data[sizeof(newN->Data) - 1] = '\0'; // Null-terminate the string in newN->Data

    // Find the last Node in the LL
    struct Node* lastN = L;
    while (lastN->Next != NULL) {
        lastN = lastN->Next;
    }

    // Insert at the end of the LL
    lastN->Next = newN;
    newN->Prev = lastN;
}




/// Print the elements (Strings) of the LL
void printList(struct Node* L) {

    struct Node* T = L->Next;// Create a temporary

    // print the String of each node
    while (T != NULL) {
        printf("%s ", T->Data);
        T = T->Next;
    }
    printf("\n");
}



///deleting the entire linked list and freeing the memory allocated for each node
void DeleteList(struct Node* L) {
    // Initialize current and nextN pointers
    struct Node* current = L;
    struct Node* nextN;

    // Traverse the list and free memory for each node
    while (current != NULL) {

        nextN = current->Next; // Store the next node's address

        free(current); // Free memory for the current node

        current = nextN; // Move to the next node
    }

    // Reset the list's pointers
    L->Next = NULL;
    L->Prev = NULL;
}



///calculates the length of the LL
int size(struct Node* L) {
    // Initialize a pointer to the first node
    struct Node* P = L->Next;

    // Initialize a counter for the num of nodes
    int length = 0;

    // count the number of nodes
    while (P != NULL) {

        length += 1; // Increment the counter
        P = P->Next; // Move to the next node

    }

    // the final length of LL
    return length;
}



///calculate the maximum length of Strings stored in the LL
int FindMaxLength(struct Node* L) {
    // Check if the LL is empty
    if (IsEmpty(L)) {
        return 0;
    }

    // the maximum length
    int maxL = 0;

    // pointer to the first node in the LL
    struct Node* P = L->Next;

    // find the maximum length
    while (P != NULL) {

        // Find the length of the current node's string
        int length = strlen(P->Data);

        // Update the maximum length
        if (length > maxL) {

            maxL = length;

        }

        // Move to the next node
        P = P->Next;
    }

    // maximum length
    return maxL;
}



///adds spaces to the strings , so that all the strings have the same length
void addSpace(struct Node* L) {
    // Find the maximum length of the Strings
    int maxL = FindMaxLength(L);

    // point to the first node in the list
    struct Node* F_node = L->Next;

    // add spaces to each node's string
    while (F_node != NULL) {
        // Get the length of the current node's string
        int num_str = strlen(F_node->Data);


        // Calculate the number of spaces to add
        int spaces_num = maxL - num_str;

        // Add spaces to the current node's string
        for (int i = 0; i < spaces_num; i++) {
            strncat(F_node->Data, " ", sizeof(F_node->Data) - strlen(F_node->Data) - 1);

        }

        // Move to the next node
        F_node = F_node->Next;
    }
}



/// the Radix Sort algorithm to sort a linked list
void RadixSort(struct Node* L) {

    // Find the maximum length of the data in the list
    int maxLen = FindMaxLength(L);

    // Add spaces to make all the strings the same length
    addSpace(L);


    // Create an array of linked lists
    struct Node* R_array[63];//   Size is 63 for space, numbers, uppercase, and lowercase letters

    // Initialize each element of the array ( empty linked list for each Position )
    for (int x = 0; x < 63; x++) {
        R_array[x] = MakeEmpty(NULL);
    }

    // Radix Sort from right to left (string )
    for (int P = maxLen - 1; P >= 0; P--) { // P is the Position

        // distribute nodes into the array
        struct Node* current = L->Next;
        while (current != NULL) {

            int index;

            //  the current character
            char currentC = current->Data[P];

            if (currentC == ' ') { //space
                index = 0;
            }
            else if ('0' <= currentC && currentC <= '9') {// numbers
                index = currentC - '0' + 1;
            }
            else if ('A' <= currentC && currentC <= 'Z') {// uppercase letters

                index = currentC - 'A' + 11;
            }
            else if ('a' <= currentC && currentC <= 'z') {// lowercase letters

                index = currentC - 'a' + 37;
            }

            Insert(current->Data, R_array[index]);
            current = current->Next;
        }

        // Make a new list and combine the array's nodes back into the first list.
        struct Node* newL = MakeEmpty(NULL);

        for (int i = 0; i < 63; i++) {
            struct Node* current = R_array[i]->Next;
            while (current != NULL) {

                // Insert the current node into the new list
                Insert(current->Data, newL);

                // Free the memory of the current
                struct Node* Temp = current->Next;
                free(current);
                current = Temp;
            }

           // For the following , reset the array index to an empty list.
            R_array[i]->Next = NULL;
        }

        // the original list's point to the new list
        L->Next = newL->Next;
    }

    // Delete the remaining nodes in each array index
    for (int i = 0; i < 63; i++) {
        DeleteList(R_array[i]);
    }
}



///read the strings from the input  file and insert them into a LL
void Load_the_strings(struct Node* L) {


    FILE* Infile = fopen("input.txt", "r");

    // Check if the file was opened successfully
    if (Infile == NULL) {

        perror("Error ... !");

        return;
    }
    else {
        printf("File opened successfully !\n");
         }


    char The_Word[31];

    // Read strings from the file and insert them into the linked list
    while (fscanf(Infile, "%30s", The_Word) == 1) {
       if(!isdigit(The_Word[0])){
        Insert(The_Word, L);}
    }

    // Close the file
    fclose(Infile);
    printf("The File closed successfully !\n");
}



///print the sorted linked list
void Print_Sorted_Strings(struct Node* L) {

    printf("Sorted Strings:\n");

    // Print the contents of the linked list
    printList(L);
}



///saving the sorted linked list in output file
void Save_To_File(struct Node* L) {

    // Open the output file ( write mode )
    FILE* Ofile = fopen("output.txt", "w");

    // Check if the file was opened
    if (Ofile == NULL) {
        printf("Error ! \n");
    }

    // write each string to the file

    struct Node* Current = L->Next;
    while (Current != NULL) {
        fprintf(Ofile, "%s\n", Current->Data);
        Current = Current->Next;
    }

    // Close the file
    fclose(Ofile);
    printf("Sorted strings are saved !\n");
}



///enter a new word and adds it to the linked list & sort it
void Add_New_Word(struct Node* L) {

    char new_Word[31];

    // Prompt the user to enter a new word
    printf("Enter the new word: ");
    scanf("%30s", new_Word);

    // Insert the new word into the linked list
    if(!isdigit(new_Word[0])){
    Insert(new_Word, L);}

    // Sort the list using radix sort
    RadixSort(L);


    printf("New word added & the list is sorted !\n");
}



///display the  menu
void View_Menu() {
    printf("Menu :\n");
    printf("1 - Load the strings\n");
    printf("2 - Print the strings before sorting\n");
    printf("3 - Sort the strings\n");
    printf("4 - Print the sorted strings\n");
    printf("5 - Add a new word to the list of sorted strings (and sort it)\n");
    printf("6 - Delete a word from the sorted strings\n");
    printf("7 - Save to output file\n");
    printf("8 - Exit\n");
    printf("Enter your choice :\n");
}



///get the choice
int The_Choice() {

    int x;

    // Read an the choice from the user
    scanf("%d", &x);

    // Return the value entered
    return x;
}



/// Perform actions based on the choice
void Menu_Choice(struct Node* list, int choice) {

    switch (choice) {
        case 1:
            Load_the_strings(list);
            break;
        case 2:
            printList(list);
            break;
        case 3:
            RadixSort(list);
            printf("The Radix Sort Is Done !\n");
            break;
        case 4:
            Print_Sorted_Strings(list);
            break;
        case 5:
            Add_New_Word(list);
            break;
        case 6:
            Delete_Word(list);
            break;
        case 7:
            Save_To_File(list);
            break;
        case 8:
            DeleteList(list);
            printf("Exit ... \n");
            exit(0);
        default:
            printf("Error ! Please try again.\n");
    }
}
