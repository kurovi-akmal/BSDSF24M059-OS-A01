# Report Questions

## 1. Explain the linking rule in this part's Makefile: `$(TARGET): $(OBJECTS)`. How does it differ from a Makefile rule that links against a library?

The rule:

```makefile
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
```

means that the target executable depends directly on the object files. Before creating `$(TARGET)`, Make ensures that all the required object files have been compiled. The linker then combines these object files to produce the final executable.

For example:

```text
main.o + mystrfunctions.o + myfilefunctions.o
                    ↓
                 client
```

A Makefile rule that links against a library is different because the library is provided as a separate input to the linker.

For example:

```makefile
$(TARGET): $(MAIN_OBJ) $(STATIC_LIB)
	$(CC) $(MAIN_OBJ) $(STATIC_LIB) -o $(TARGET)
```

Here, `main.o` is linked with `libmyutils.a` rather than directly linking all of the utility object files.

For a dynamic library, the linker can use:

```bash
gcc main.o -L../lib -lmyutils -o client_dynamic
```

In this case, `-L../lib` tells the linker where to search for the library and `-lmyutils` specifies the library named `libmyutils.so` or `libmyutils.a`.

Therefore, direct object linking combines object files directly, while library linking uses a separately packaged library containing reusable compiled code.

---

## 2. What is a Git tag and why is it useful in a project? What is the difference between a simple tag and an annotated tag?

A Git tag is a named reference to a specific commit in a Git repository. Tags are useful for marking important points in the project's history, such as completed features, versions, or final releases.

For example, this project uses tags such as:

```text
v0.1.1-multifile
v0.3.1-dynamic
v0.4.1-final
```

A **simple/lightweight tag** is essentially just a pointer to a commit. It does not contain additional tag information.

Example:

```bash
git tag v1.0
```

An **annotated tag** is a Git object that stores additional information, including the tag creator, date, message, and the referenced commit.

Example:

```bash
git tag -a v1.0 -m "Version 1.0"
```

Annotated tags are useful for official releases because they provide additional information and clearly document why the tag was created.

---

## 3. What is the purpose of creating a "Release" on GitHub? What is the significance of attaching binaries like your client executable to it?

A GitHub Release provides a formal, user-friendly way to publish a specific version of a project. A release is normally associated with a Git tag and can contain release notes and downloadable files.

For this project, the final release is associated with:

```text
v0.4.1-final
```

Attaching binaries such as the compiled `client` executable is useful because users can download and run the already-built program without having to clone the repository, install the development tools, and compile the source code themselves.

For example, instead of requiring a user to compile:

```text
main.c
mystrfunctions.c
myfilefunctions.c
```

the release can provide the already-built executable.

This also preserves a specific compiled version of the project alongside its source code, making the release easier to distribute and reproduce.

---

## 4. What is Position-Independent Code (`-fPIC`) and why is it a fundamental requirement for creating shared libraries?

Position-Independent Code (PIC) is machine code that can execute correctly regardless of where it is loaded into memory.

The compiler option:

```bash
-fPIC
```

tells GCC to generate position-independent code.

In this project, separate PIC object files were created:

```text
mystrfunctions_pic.o
myfilefunctions_pic.o
```

These were then used to create:

```text
libmyutils.so
```

PIC is important for shared libraries because a shared library may be loaded at different virtual memory addresses in different processes. The code should not depend on being loaded at one fixed address.

Using position-independent code allows the operating system's dynamic loader to map the same shared library into different processes at suitable memory locations without requiring the library's machine code to be rewritten for each process.

This makes shared libraries practical and allows multiple programs to use the same library in memory.

---

## 5. Explain the difference in file size between your static and dynamic clients. Why does this difference exist?

The project produced both a statically linked client and a dynamically linked client:

```text
bin/client_static
bin/client_dynamic
```

The sizes observed during the build were approximately:

```text
client_static   ≈ 14 KB
client_dynamic  ≈ 13 KB
```

The exact sizes can vary depending on the compiler, linker, system libraries, and build options.

The main reason for the difference is how the custom library code is provided to the executable.

With **static linking**, the required code from `libmyutils.a` is copied into the executable during linking. Therefore, the executable contains its required custom library code.

With **dynamic linking**, the executable does not contain the complete implementation of the shared library. Instead, it contains information indicating that it needs `libmyutils.so`. The shared library is loaded separately at runtime.

Therefore, dynamically linked executables are generally smaller because library code is kept outside the executable. The shared library can also be shared by multiple programs.

In this project, the difference was relatively small because the custom library itself is small. The executable also contains other components such as program code and runtime/linking information, so the size difference is not necessarily equal to the size of the library.

---

## 6. What is the `LD_LIBRARY_PATH` environment variable? Why was it necessary to set it for your program to run, and what does this tell you about the responsibilities of the operating system's dynamic loader?

`LD_LIBRARY_PATH` is an environment variable used on Linux systems to specify additional directories where the dynamic loader should search for shared libraries.

The project created the shared library inside:

```text
lib/libmyutils.so
```

This is a project-local directory and is not normally one of the standard system library directories.

Therefore, when running:

```text
bin/client_dynamic
```

the dynamic loader needed to be told where to find `libmyutils.so`.

This can be done with:

```bash
export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
```

After setting this variable, the loader can search the project's `lib` directory and find the required shared library.

This demonstrates that dynamic linking has two separate stages:

1. **Link time:** the linker records that the executable requires `libmyutils.so`.
2. **Run time:** the dynamic loader must locate and load the required shared library.

The operating system's dynamic loader is therefore responsible for locating the required shared libraries, loading them into the process's address space, and resolving the necessary runtime dependencies.

The need for `LD_LIBRARY_PATH` also demonstrates why shared libraries normally need to be installed in standard library locations or otherwise made discoverable to the dynamic loader.
