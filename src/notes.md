
* NEW IDEA:
New class : Serializer or something, that can be 'loaded' with objects of various types
(as void pointers?). When Serializer::serialize() is called, a buffer is allocated, and
for each of the loaded objects, a ->serialize() function call is issued. This deep-copies
the serialized object into the buffer and returns the size of the serialized object so
that the buffer pointer may be incremented correctly for the next object.

E.g.
uint32_t State::serialize(char** buffer) is called from Serializer::serialize():
    char* buffer = new char[MAX_BUFFER_SZ];
    memset(buffer, 0, MAX_BUFFER_SZ);
    // serialize the State and write into buffer
    uint32_t state_size = State::serialize(char** buffer);
    buffer += state_size;
    // next object..
    // ...

Problem: is it possible to keep references/pointers to objects of unknown type? Is it
possible to call unknown_object->serialize(), or does all object have to inherit from the 
same base class? Can static classes have this type of inheritance?
    -- Solution : since all functions will have the same signatures (ie. args and return 
                  type), function pointers should be used (std::function<> and std::bind()
                  for member functions).
    -- New problem : de-serialization has to be performed in the same order, and the 
                     Serializer has to have some kind of hook/reference to the objects 
                     to be loaded (after de-serialization). This should be doable with
                     Serializer::register_object() taking both a serializer and a de-
                     serializer function pointer as arguments, which are the appended to
                     separate vectors.

