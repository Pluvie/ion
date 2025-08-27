int reflection_path_print (
    struct reflection* rfx,
    string result
)
{
  if (rfx == NULL)
    return 0;

  struct reflection* node = rfx;
  struct reflection* nodes[32] = { 0 };
  string printer = { result.pointer, result.length };
  int nodes_count = 0;

climb_reflection:
  if (node->parent != NULL && node->parent->type == POINTER) {
    node->name = node->parent->name;
    node->parent->name = (string) { 0 };
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
  int printed_bytes = 0;
  int node_depth = nodes_count - 1;

loop_nodes:
  node = nodes[node_depth];
  printed_bytes = 0;

  if (!eq(node->name, NULL)) {
    if (node_depth == 0)
      printed_bytes = string_print(printer, "%.*s", sp(node->name));
    else
      printed_bytes = string_print(printer, "%.*s.", sp(node->name));

    goto previous_node;
  }

  if (node->parent != NULL &&
      (node->parent->type == ARRAY ||
       node->parent->type == LIST)) {

    if (node_depth == 0)
      printed_bytes = string_print(printer, "%li", node->index);
    else
      printed_bytes = string_print(printer, "%li.", node->index);

    goto previous_node;
  }

previous_node:
  if (printed_bytes < 0)
    goto print_error;

  printer.pointer += printed_bytes;
  printer.length -= printed_bytes;
  node_depth--;

  if (node_depth < 0)
    return printed_bytes;

  goto loop_nodes;

print_error:
  zero_out(result.pointer, result.length);
  return printed_bytes;
}
