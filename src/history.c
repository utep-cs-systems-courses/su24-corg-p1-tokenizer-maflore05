#include "history.h"
#include "malloc.h"
#include "tokenizer.h"
#include <string.h>

List* init_history(){
  List *hist_list = malloc(sizeof(List));
  hist_list->root = 0;
  return hist_list;
}

void add_history(List *list, char*str){
  Item *curr_item = 0;
  int loc = 1;
  size_t buff_size = strlen(str)+1;
  char *newStr = (char*)malloc(buff_size*sizeof(char));
  strcpy(newStr, str);
  if(list->root){
    curr_item = list->root;
    while(curr_item->next){
      curr_item = curr_item->next;
      loc++;
    }
  }
  else{
    Item *newItem = (Item*)malloc(sizeof(Item));
    newItem->id = 0;
    newItem->str = newStr;
    list->root = newItem;
  }
  if(curr_item){
    Item *newItem = (Item*)malloc(sizeof(Item));
    newItem->id = loc;
    newItem->str = newStr;
    curr_item->next = newItem;
  }
}

char *get_history(List *list, int id){
  char err = '\n';
  char *errP = &err;
  if(list->root){
    Item *curr_node = list->root;
    int old = id;

    while(curr_node && id>0){
      curr_node = curr_node->next;
      id--;
    }
    if(id == 0 && curr_node != 0){
      return (*curr_node).str;
    }
    else{
      printf("ID out of range\n");
      return errP;
    }
  }
  else{
    printf("No history yet!\n");
    return errP;
  }
}

void print_history(List *list){
  if(list->root){
    int loc = 0;
    Item *curr_node = list->root;
    while(curr_node){
      printf("History at %d: %s", loc, curr_node->str);
      curr_node = curr_node->next;
      loc++;
    }
  }
  else{
    printf("No history yet!\n");
  }
}

void free_history(List *list){
  if(list->root){
    Item *curr_node = list->root;
    Item *next_node = curr_node;
    while(curr_node != 0){
      next_node = curr_node->next;
      //printf("Freeing %s", curr_node->str);
      free(curr_node->str);
      free(curr_node);
      curr_node = next_node;
    }
  }
  free(list);
  printf("Sucessfully freed memory!\n");
}
