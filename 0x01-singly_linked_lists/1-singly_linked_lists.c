#include <stdio.h>
#include <stdlib.h>

/**
 * List_Node - Structure of a node in the list
 * @value : value of a node in the list
 * @next : pointer to the next node of type List_Node
*/
typedef struct List_Node{
    int value;
    struct List_Node *next;
} List_Node;


/**
 * add_to_end - function that adds an element at the end of the list
 * @head : the head of the singly linked list
 * @value : value of the node that is supposed to be added to the list
 * Return : the added node
*/
List_Node insert_to_end(List_Node **head, int value)
{
    // allocate memory for this new node
    List_Node *new_node = malloc(sizeof(List_Node));
    // check if the memory has been allocated and exit if not
    if (new_node == NULL){
        exit(1);
    }
    // set the values for the list node
    new_node->value = value;
    new_node->next = NULL;
    // if there is no head in the singly linked list, make this node the head
    if (*head == NULL){
        *head = new_node;
        return *new_node;
    }
    // otherwise, loop to the end and add this node there
    List_Node *current = *head;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = new_node;
    return *new_node;
}

/**
 * insert_at_beginning - inserts a node at the beginning of a list
 * @head : the head of the singly linked list
 * @value : the value of the node that is supposed to be added to the list
*/
List_Node insert_at_beginning(List_Node **head, int value){
    List_Node *new_node = malloc(sizeof(List_Node));

    if (new_node == NULL){
        exit(1);
    }
    new_node->value = value;
    new_node->next = NULL;
    // if there are completely no elements in the list, make this node the head
    if (*head == NULL){
        *head = new_node;
        return *new_node;
    }
    // if there are elements in the list
    // make this node point to the current head
    // explicitly make it to be the head
    new_node->next = *head;
    *head = new_node;
    return *new_node;
}

/**
 * get_list_length - gets the length of the singly linked list
 * @head : the head of the singly linked list
 * Return : the length of the list
*/
int get_list_length(List_Node **head){
    // if there are no elements, return 0
    if (*head == NULL){
        return (0);
    }

    // otherwise, loop as you count
    List_Node *current = *head;
    int length;

    length = 0;

    while (current != NULL)
    {
        length++;
        current = current->next;
    }
    return length;
    
}

/**
 * get - gets the node at a given index in the list
 * @head : pointer to the head of the singly linked list
 * @idx : the index of the node that we are supposed to get
 * Return : the node at index @idx following the zero indexing
*/
List_Node *get(List_Node **head, int idx){
    // if there are no nodes in the list, return NULL
    if (*head == NULL){
        return NULL;
    }
    // idx should be greater than 0 and less than list length, validate this
    int list_length = get_list_length(head);
    if (idx <0 && idx >= list_length){
        return (NULL);
    }
    // if the idx is 0, just return the head
    if (idx == 0){
        return *head;
    }
    // otherwise, loop until you get the element
    List_Node *current = *head;
    int i = 0;
    while (i < idx)
    {
        i++;
        current = current->next;
    }
    return current;
}

/**
 * insert_middle - inserts a node in the middle of a list at a given index
 * @head : pointer to the head of a singly linked list
 * @value : value of the new node that is supposed to be added
 * @idx : index at which to insert the new node
 * Return : the added node
 * Description: the method follows zero based indexing
*/
List_Node insert_middle(List_Node **head, int value, int idx){
    // if the index is zero, we insert at the beginning
    if (idx == 0){
        return (insert_at_beginning(head, value));
    }

    // if idx is equal to length of list - 1, we add it to the end
    int list_length = get_list_length(head);
    if (idx == list_length-1){
        return (insert_to_end(head, value));
    }

    // allocate memory for this new node
    List_Node *new_node = malloc(sizeof(List_Node));
    if (new_node == NULL){
        exit(1);
    }
    new_node->value = value;
    new_node->next = NULL;

    // we use get to get the node just before the index we want to insert
    List_Node *node_before = get(head, idx - 1);
    // get what node before is currently pointing to
    List_Node *tmp = node_before->next;
    // insert in the middle of the node before and tmp
    node_before->next = new_node;
    new_node->next = tmp;
    return *new_node;
}

/**
 * remove_end - removes a node at the end of the list
 * @head : pointer to the head of the singly linked list
 * Return: the removed node
*/
List_Node *remove_end(List_Node **head){
    // if there are no elements in the list, return NULL
    if (*head == NULL){
        return (NULL);
    }

    // Get the list length
    int list_length = get_list_length(head);
    // get the last node so that we return it at the end
    // tap into power of list_length - 1 and the get function
    List_Node *last_node = get(head, list_length - 1);
    //use get to get second last node and set it's next property to be null
    List_Node *second_last_node = get(head, list_length-2);
    second_last_node->next = NULL;
    // free the removed node
    free(last_node);
    return (last_node);
}

/**
 * remove_beginning : removes a node at the beginning of the list
 * @head : pointer to the head of the singly linked list
 * Return : the removed node
*/

List_Node *remove_beginning(List_Node **head){
    // if there are no elements in the list, return NULL
    if (*head == NULL){
        return (NULL);
    }
    // otherwise, get the current head
    List_Node *current_head = *head;
    // make the head to be the next of the current head
    *head = current_head->next;
    // make the current head's next to be null and free it
    current_head->next = NULL;
    free(current_head);
    return (current_head);
}

/**
 * remove_middle - removes a node in the middle of the list
 * @head : the head of the singly linked list
 * @idx : the index of the node to be removed
 * Return: the removed node
*/

List_Node *remove_middle(List_Node **head, int idx){
    // if the list is empty, return null
    if (*head == NULL){
        return NULL;
    }
    // if the indexis zero, we call the function that removes the head
    if (idx == 0){
        return (remove_beginning(head));
    }
    // if the index is equal to length of the list minus 1, we remove at end
    int list_length = get_list_length(head);
    if (idx == list_length-1){
        return (remove_end(head));
    }

    // otherwise, use get to get the node before the node to be removed
    List_Node *node_before = get(head, idx-1);
    // use get to get the node to be removed
    List_Node *removed_node = get(head, idx);
    // make this node before next point to removed node next
    node_before->next = removed_node->next;
    // make the removed node next to be null then free and return it
    removed_node->next = NULL;
    free(removed_node);
    return (removed_node);
}

/**
 * set - changes the value of a node in the list
 * @head : the head of the singly linked list
 * @idx : the index of the node being changed
*/
List_Node *set(List_Node **head, int value, int idx){
    // use get to get the node that should be changed
    // it already handles the idx validation
    List_Node *node_to_be_changed = get(head, idx);
    node_to_be_changed->value = value;
    return node_to_be_changed;
}

/**
 * reverse_list - reverses the list in place
 * @head : the head of the singly linked list
 * Return: the head of the singly linked list
*/

List_Node *reverse_list(List_Node **head){
    // if there are no elements, return null
    if (*head == NULL){
        return (NULL);
    }
    List_Node *previous = NULL;
    List_Node *current = *head;
    List_Node *next = current->next;
    while(current->next != NULL){
        current->next = previous;
        previous = current;
        current = next;
        next = current->next;
    }
    current->next = previous;
    *head = current;
    return (*head);
}

/**
 * print_list - prints the singly linked list
 * @head : the head of the singly linked list
*/

void print_list (List_Node **head){
    List_Node *current = *head;
    while (current != NULL){
        printf("%d->", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main(void)
{
    // initializing the singly linked list
    List_Node *head = NULL;
    insert_to_end(&head, 10);
    insert_to_end(&head, 15);
    insert_to_end(&head, 20);

    // inserting at the beginning
    insert_at_beginning(&head, 5);
    insert_at_beginning(&head, 4);
    insert_at_beginning(&head, 3);

    // getting a node
    printf("%d\n", get(&head, 3)->value);

    // inserting in the middle
    insert_middle(&head, 8, 3);
    insert_middle(&head, 1, 0);
    insert_middle(&head, 25, 7);

    // removing at the end
    remove_end(&head);

    // removing at the beginning
    remove_beginning(&head);

    // removing in the middle
    remove_middle(&head, 0);
    remove_middle(&head, 5);
    remove_middle(&head, 2);

    // changing the value of a node
    set(&head, 2, 0);

    // getting the length of the list
    printf("Length of the list: %d\n", get_list_length(&head));

    // printing/traversing the list
    print_list(&head);
    
    // reversing the list
    reverse_list(&head);
    print_list(&head);
}