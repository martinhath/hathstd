#hathstd.h

The C standard library is small - perhaps a little too small?
In any case, I've decided to write a little library for myself, containing stuff I might find useful.

### Notes

 - For all functions that returns an `int` for errors, zero is failure.

## Containers

### `List`

TODO: write 

### `Array`

The point of having a `Array` type is, well, it's convenient. The array is **safe**, meaning it checks indexes on every call (similar to what Java does).
The main point of this container is to not have to think about the size of the array, and related problems (resizing, for instance).
There are also some convenient funcions, such as `array_clone`, `array_foreach`. and `array_map`.

| Function name | description | 
|---------------|-------------|
| `Array *array_create(void)` | Creates a new array |
| `void array_free(Array*)` | Frees the array |
| `void *array_get(Array*, size_t)`   | Retrieves the element at the specified index |
| `int array_add(Array*, void*)` | Inserts an element at the end of the array |
| `int array_set(Array*, size_t, void*)` | Inserts an element at the specified index |
| `size_t array_size(Array*)` | Returns the number of elements in the array |
| `Array *array_clone(Array*)` | Clones the array, returning a new. The `void*` are only copied, meaning they will point to the same data as the original array |
| `void array_foreach(Array*, void (*f)(void*))` | Runs the given function on all members of the array |
| `Array *array_map(Array*, void *(*f)(void*))` | Creates a new array where each element is `e=f(a)` for all `a` in the given array |

Note the difference between `foreach` and `map`. Also note that you should use `array_free` instead of calling `free()` yourself.
