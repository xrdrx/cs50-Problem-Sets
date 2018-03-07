# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

 longest word in the English language published in a dictionary

## According to its man page, what does `getrusage` do?

 get resource usage

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

not spending resources copying

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

read each character while it's letter or ' and add it to "word", index indicates number of letters in a word. End word with \0 and spellcheck, set index to 0 for checking new word

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

we don't know how files are formatted

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

because dictionary and text file are constant and won't be changing
