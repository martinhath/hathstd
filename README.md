#hathstd.h

The C standard library is small - perhaps a little too small?
In any case, I've decided to write a little library for myself, containing stuff I might find useful.

## Containers

### `List`

TODO: write 

### `Array`

The point of having a `Array` type is, well, it's convenient. The array is **safe**, meaning it checks indexes on every call (similar to what Java does).
The main point of this container is to not have to think about the size of the array, and related problems (resizing, for instance).
There are also some convenient funcions, such as `array_clone`, `array_foreach`. and `array_map`.

| Function name | description | 
|---------------|-------------|
| `array_create(void)` | Creates a new array |
| `array_get(Array*, size_t)` | Retrieves the element at an index |

TODO: more
