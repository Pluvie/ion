static inline i32 protocol_path_print (
    struct protocol* p,
    char* result,
    u64 length
)
{
  struct reflect* node = p->schema;

  if (node == NULL)
    return 0;

  struct array nodes = array_init(sizeof(struct reflect), 8, p->allocator);

climb_schema:
  array_push(&nodes, node);

  if (node->parent != NULL) {
    node = node->parent;
    goto climb_schema;
  }

reverse_print:
  i32 printed_bytes = 0;
  u32 print_cursor = 0;
  i32 node_index = nodes.length - 1;

loop_nodes:
  node = array_get(&nodes, node_index);

  if (node->name != NULL) {
    if (node_index == 0)
      printed_bytes = snprintf(result, length - print_cursor, "%s", node->name);
    else
      printed_bytes = snprintf(result, length - print_cursor, "%s.", node->name);

    goto previous_node;
  }

  if (node->parent != NULL &&
      (node->parent->type == ARRAY || node->parent->type == SEQUENCE)) {

    if (node_index == 0)
      printed_bytes = snprintf(result, length - print_cursor, "%i", node->index);
    else
      printed_bytes = snprintf(result, length - print_cursor, "%i.", node->index);

    goto previous_node;
  }

previous_node:
  if (printed_bytes < 0)
    goto print_error;

  result += printed_bytes;
  print_cursor += printed_bytes;
  node_index--;

  if (node_index < 0)
    return print_cursor;

  goto loop_nodes;

print_error:
  bzero(result, length);
  return printed_bytes;
}
