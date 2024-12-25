template<typename T>
inline PriorityQueue<T>::PriorityQueue(func f) : front(nullptr), rear(nullptr), size(0), f(f) {}

template<typename T>
inline PriorityQueue<T>::PriorityQueue(const PriorityQueue& other)
{
    try
    {
        copy(other);
    }
    catch (std::runtime_error&)
    {
        free();
        throw;
    }
}

template<typename T>
inline PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue& other)
{
    if (this != &other)
    {
        try
        {
            copy(other);
        }
        catch (std::runtime_error&)
        {
            free();
            throw;
        }
    }
    return *this;
}

template<typename T>
inline PriorityQueue<T>::~PriorityQueue()
{
    free();
}

template<typename T>
inline void PriorityQueue<T>::enqueue(const T& data)
{
    Node* newNode = new (std::nothrow) Node(data);
    if (!newNode)
    {
        throw std::runtime_error("unable to allocate new memory of the queue");
    }

    // Case 1: Empty queue
    if (!front)
    {
        front = rear = newNode;
        size++;
        return;
    }

    // Case 2: Insert at the front (highest priority)
    if (f(newNode->data, front->data))
    {
        newNode->next = front;
        front = newNode;
        size++;
        return;
    }

    // Case 3: Insert in the somewhere in the middle or at the end
    Node* prev = front;
    Node* current = front->next;

    while (current && !f(newNode->data, current->data))
    {
        prev = current;
        current = current->next;
    }

    // Insert the new node
    newNode->next = current;
    prev->next = newNode;

    // Update rear if inserted at the end
    if (!current)
    {
        rear = newNode;
    }

    size++;
}

template<typename T>
inline void PriorityQueue<T>::dequeue()
{
    if (!front)
    {
        throw std::out_of_range("queue is empty");
    }

    Node* tmp = front;
    front = front->next;

    if (!front)
    {
        rear = nullptr;
    }

    size--;
    delete tmp;
}

template<typename T>
inline const T& PriorityQueue<T>::peek() const
{
    if (!front)
    {
        throw std::out_of_range("queue is empty");
    }
    return front->data;
}

template<typename T>
inline bool PriorityQueue<T>::isEmpty() const
{
    return size == 0;
}

template<typename T>
inline std::size_t PriorityQueue<T>::length() const
{
    return size;
}

template<typename T>
inline void PriorityQueue<T>::free()
{
    while (front)
    {
        Node* tmp = front;
        front = front->next;
        delete tmp;
    }
    this->size = 0;
}

template<typename T>
inline void PriorityQueue<T>::copy(const PriorityQueue& other)
{
    this->front = nullptr;
    this->rear = nullptr;
    f = other.f;
    Node* current = other.front;
    while (current)
    {
        enqueue(current->data);
        current = current->next;
    }
}
