# 🔍 Gerp: Fast Word Indexing and Search  

**Authors**: Duncan Johnson, Eddy Zhang  

📌 **Project Documentation:** [Gerp Replica](https://narrow-theory-18d.notion.site/grep-Replica-1b9436c3d41a817daa64ff16b9604219?pvs=74)  

## 📝 Purpose  
Gerp is a powerful word indexing and searching tool that processes an entire directory, indexing words efficiently to allow **fast retrieval** of all lines containing a queried word. It supports **case-sensitive** and **case-insensitive** searches and allows users to specify an output file for search results.  

## 🚀 How It Works  
1. **Indexing Phase:**  
   - Recursively traverses a directory and processes each file.  
   - Extracts words and indexes them in **two hash tables** (case-sensitive and lowercase).  
   - Stores the original text lines in a **vector** for quick retrieval.  

2. **Search Phase:**  
   - Users enter words to search.  
   - Retrieves matching lines using hash tables and outputs them to a specified file.  

---

## 📁 Program Files  

- **`main.cpp`**  
  - Handles command-line arguments and initializes Gerp.  
- **`Gerp.h` & `Gerp.cpp`**  
  - Implements the core search engine, manages hash tables, and runs the interactive search loop.  
- **`HashTable.h` & `HashTable.cpp`**  
  - Implements a **chaining-based hash table** for efficient word indexing.  
- **`unit_tests.h`**  
  - Contains automated tests for Gerp's functionality.  
- **`Makefile`**  
  - Build automation for compiling and running tests.  

---

## ⚙ Compiling and Running  

### **Compile Gerp**  
```bash
make gerp
```

### **Run Gerp**  
```bash
./gerp DirectoryToIndex OutputFile
```
- `DirectoryToIndex` → The directory to search.  
- `OutputFile` → The file where results will be written.  

---

## 🏗 Architectural Overview  

### **Core Data Structures**  
- **Vector of Text Lines:** Stores all original file lines for fast retrieval.  
- **Case-Sensitive Hash Table:** Maps words to their line indices.  
- **Lowercase Hash Table:** Supports case-insensitive searches.  

### **Hash Table Design**  
- Implemented using an **array of buckets** with **chaining** for collision resolution.  
- Each bucket stores a **linked list** of `KeyValue` pairs:  
  - **Key:** The word.  
  - **Value:** A list of line numbers where the word appears.  
- Automatically resizes when load factor exceeds **70%**.  

### **Indexing Algorithm**  
1. Recursively traverses directories and reads files.  
2. Processes each line, extracts words, and normalizes them.  
3. Inserts words into **both hash tables** (case-sensitive and lowercase).  
4. Stores the **entire line** for fast retrieval when a match is found.  

### **Search Algorithm**  
1. Looks up the word in the appropriate hash table.  
2. Retrieves the list of line indices.  
3. Outputs matching lines, formatted as:  
   ```
   filepath:line_number: text
   ```

---

## 🛠 Testing and Validation  

1. **Unit Tests:**  
   - Hash table insertion, retrieval, and expansion.  
   - File parsing and directory traversal.  
   - Case-sensitive and case-insensitive searches.  

2. **Integration Testing:**  
   - Diff testing against a reference implementation.  
   - **Valgrind memory leak analysis** to ensure correctness.  

---

## 📌 Key Features & Optimizations  

✅ **Fast Word Lookup** using hash tables (O(1) average lookup time).  
✅ **Handles Large Text Datasets** with efficient indexing.  
✅ **Supports Case-Insensitive Searches** via dual hash table indexing.  
✅ **Automatically Expands Hash Table** to maintain performance.  
✅ **Memory-Optimized Storage** using linked lists and hash buckets.  

---

📂 *For full documentation and implementation details, refer to the [Notion Project Page](https://narrow-theory-18d.notion.site/grep-Replica-1b9436c3d41a817daa64ff16b9604219?pvs=74).*  
