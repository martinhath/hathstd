#hathstd.h

The C standard library is small - perhaps a little too small?
In any case, I've decided to write a little library for myself, containing stuff I might find useful.

### Notes

 - For all functions that returns an `int` for errors, zero is failure.
 - For containers, the elements you insert into the container are not freed. This means if you create a list of strings, and call `list_free(list)`, the strings will not be freed. You will have to to this yourself.

## Usage

The following sample program should build, and run correctly.

```c
// sample.c
#include <hathstd.h>
#include <stdio.h>

void print(void*);

int main() {
    Array *array = array_create();
    array_add(array, "hath");
    array_add(array, "std");
    array_add(array, "just");
    array_add(array, "werks!");
    array_foreach(array, print);
    printf("\n");
    return 0;
}

void print(void *s) {
    printf("%s ", s);
}
```

Compile with 

```bash
clang -lhathstd sample.c -o sample
./sample // "hath std just werks!"
```

### Installation

Simply run

```bash
make
make install
```

## Containers

### `List`

| Function name | Description | Complexity | 
|---------------|-------------|------------|
| `List *list_create(void)` | Creates a new list | O(1) |
| `void list_free(List*)` | Frees the list | O(n) |
| `List *list_push(List*, void*)` | Adds the element at the front of the list | O(1) |
| `List *list_push_back(List*, void*)` | Adds the elements at the back of the list | O(n) |
| `void *list_pop(List*)` | Pops the first element of the list | O(1) |
| `void *list_pop_back(List*)` | Pops the last element of the list | O(n) |
| `void *list_delete(List*, void*, int (*cmp)(void*, void*))` | Deletes all elements a such that `cmp(elem, a)` is `true` | O(n) |
| `void list_foreach(List*, void (*f)(void*))` | Calls `f(e)` on every element in the list | O(n) |
| `int list_empty(List*)` | Returns wether the list is empty | O(1) |
| `size_t list_size(List*)` | Returns the size of the list | O(n) |
| `int list_contains(List*, void*, int (*cmp)(void*, void*)` | Returns wether the list contains a element such that `cmp(elem, e)` is `true`. | O(n) |
| `List *list_reverse(List*)` | Reverses the list. Returnes the reversed list | O(n) |

### `Array`

The point of having a `Array` type is, well, it's convenient. The array is **safe**, meaning it checks indexes on every call (similar to what Java does).
The main point of this container is to not have to think about the size of the array, and related problems (resizing, for instance).
There are also some convenient funcions, such as `array_clone`, `array_foreach`. and `array_map`.

| Function name | Description | Complexity | 
|---------------|-------------|------------|
| `Array *array_create(void)` | Creates a new array | O(1) |
| `void array_free(Array*)` | Frees the array | O(n) |
| `void *array_get(Array*, size_t)`   | Retrieves the element at the specified index | O(1) |
| `int array_add(Array*, void*)` | Inserts an element at the end of the array | O(1) |
| `int array_set(Array*, size_t, void*)` | Inserts an element at the specified index | O(1) |
| `size_t array_size(Array*)` | Returns the number of elements in the array | O(1) |
| `Array *array_clone(Array*)` | Clones the array, returning a new. The `void*` are only copied, meaning they will point to the same data as the original array | O(n) |
| `void array_foreach(Array*, void (*f)(void*))` | Runs the given function on all members of the array | O(n) |
| `Array *array_map(Array*, void *(*f)(void*))` | Creates a new array where each element is `e=f(a)` for all `a` in the given array | O(n) |

Note the difference between `foreach` and `map`. Also note that you should use `array_free()` instead of calling `free()` yourself.

### `HashMap`

| Function name | Description | Complexity |  
|---------------|-------------|------------|
| `HashMap *hashmap_create(size_t (*hash)(void*), int (*keycmp)(void*, void*))` | Creates a new hashmap. The first function is the hashing function, which takes a key. The second function is a key compare function | O(1) |
| `HashMap *hashmap_create_str(void)` | Creates a new hashmap, where the key is of type `char*` | O(1) |
| `void hashmap_free(HashMap*)` | Frees the hashmap | O(n) |
| `int hashmap_set(HashMap*, void*, void*)` | set (key, value). Returns 0 on failure | O(1) |
| `void *hashmap_get(HashMap*, void*)` | Gets the value with the supplied key | O(1) |
| `void *hashmap_delete(HashMap*, void*)` | Deletes the item with the supplied key | O(1) |
| `size_t hashmap_size(HashMap*)` | Returns the number of elements in the map | O(n) |
| `List *hashmap_keys(HashMap*)` | Returns a `List` with all the keys in the HashMap | O(n) |

### `Tree`

| Function name | Description | Complexity |
|---------------|-------------|------------|
| `Tree *tree_create(int (*cmp)(void*, void*))` | Creates a new tree. Takes a function that compares values you put in the tree. The funcion should return as `strcmp` does. | O(1) |
| `void tree_free(Tree*)` | Frees the memory allocated. | O(n) |
| `int tree_contains(Tree*, void*)` | Returns `true` if the tree contains the given element. | O(lg n) |
| `void tree_foreach(Tree*, void (*f)(void*))` | Runs the given function on all elements. | O(n) |
| `int tree_insert(Tree*, void*)` | Insert the element into the tree | O(lg n) |
| `void *tree_delete(Tree*, void*)` | Deletes the element | O(lg n) |

