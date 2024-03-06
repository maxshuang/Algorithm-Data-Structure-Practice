// Essentially, radix tree is a multi-layer table(limited space), akin to B-tree, 
// Only leaf node allows to have the value attached to it. Use for sparse long int index.
// It's not a prefix tree like trie.
// trie => prefix tree => prefix match
// radix tree => multi-layer table => limited space => sparse presentation => static
// B/B+ => multi-layer tree => unlimited space => dense presentation => dynamic 

// redix tree can O(1) insert and O(1) search, unlimited sorted key
