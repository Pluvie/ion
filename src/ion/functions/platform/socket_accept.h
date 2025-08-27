void socket_accept (
    struct socket* sock,
    void (*connector)(struct socket*),
    int max_accepts,
    int timeout_ms
);
