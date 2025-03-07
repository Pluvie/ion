static inline i32 reflection_path_print (
    struct reflection* rfx,
    char* result,
    u64 length
)
{
  if (rfx == NULL)
    return 0;

  struct reflection* node = rfx;
  struct reflection* nodes[32] = { 0 };
  u64 nodes_count = 0;

climb_reflection:
  if (node->parent != NULL && node->parent->type == POINTER) {
    node->name = node->parent->name;
    node->parent->name = NULL;
  }

  nodes[nodes_count] = node;
  nodes_count++;

  if (nodes_count >= countof(nodes))
    goto reverse_print;

  if (node->parent != NULL) {
    node = node->parent;
    goto climb_reflection;
  }

reverse_print:
  i32 printed_bytes = 0;
  u32 print_cursor = 0;
  i32 node_index = nodes_count - 1;

loop_nodes:
  node = nodes[node_index];
  printed_bytes = 0;

  if (node->name != NULL) {
    if (node_index == 0)
      printed_bytes = snprintf(result, length - print_cursor, "%.*s", sp(node->name));
    else
      printed_bytes = snprintf(result, length - print_cursor, "%.*s.", sp(node->name));

    goto previous_node;
  }

  if (node->parent != NULL &&
      (node->parent->type == ARRAY ||
       node->parent->type == SEQUENCE ||
       node->parent->type == VECTOR)) {

    if (node_index == 0)
      printed_bytes = snprintf(result, length - print_cursor, "%li", node->index);
    else
      printed_bytes = snprintf(result, length - print_cursor, "%li.", node->index);

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
  memzero(result, length);
  return printed_bytes;
}
