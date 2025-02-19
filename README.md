# Strqueue

Strqueue is a C++ library for managing string queues. It provides functionalities to create, manipulate, and compare queues of strings.

## Features

- Create and delete string queues
- Insert and remove strings at specific positions
- Retrieve strings from specific positions
- Clear entire queues
- Compare two queues lexically

## Installation

To compile the project, use the provided `Makefile`. Ensure you have `gcc` and `g++` installed.

```sh
make
```

## Usage

### Creating a Queue

```cpp
unsigned long id = cxx::strqueue_new();
```

### Inserting a String

```cpp
cxx::strqueue_insert_at(id, 0, "example");
```

### Retrieving a String

```cpp
const char* str = cxx::strqueue_get_at(id, 0);
```

### Removing a String

```cpp
cxx::strqueue_remove_at(id, 0);
```

### Comparing Queues

```cpp
int result = cxx::strqueue_comp(id1, id2);
```

## Running Tests

To run the tests, compile the test executables using the `Makefile` and execute them.

```sh
make
./strqueue_test_1_dbg
./strqueue_test_2_dbg_a
```

## License

This project is licensed under the MIT License.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.
