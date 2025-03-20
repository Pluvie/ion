static inline const char* http_reason_phrase (
    u32 http_status
)
{
  /**
   * [RFC 7230](https://www.ietf.org/rfc/rfc7230.txt)
   * Section 3.5 - Message Parsing Robustness
   *
   * The reason-phrase element exists for the sole purpose of providing a
   * textual description associated with the numeric status code, mostly
   * out of deference to earlier Internet application protocols that were
   * more frequently used with interactive text clients.  A client SHOULD
   * ignore the reason-phrase content.
   *
   *   status-line = HTTP-version SP status-code SP reason-phrase CRLF
   *
   *   reason-phrase  = *( HTAB / SP / VCHAR / obs-text )
   */

  /**
   * https://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml
   * [RFC9110, Section 16.2.1]
   *
   * 1xx: Informational - Request received, continuing process
   * 2xx: Success - The action was successfully received, understood, and accepted
   * 3xx: Redirection - Further action must be taken in order to complete the request
   * 4xx: Client Error - The request contains bad syntax or cannot be fulfilled
   * 5xx: Server Error - The server failed to fulfill an apparently valid request
   */
  switch (http_status) {
  case 100:
    return "Continue";
  case 101:
    return "Switching Protocols";
  case 102:
    return "Processing";
  case 103:
    return "Early Hints";
  case 104:
    return "Upload Resumption";
  /* 105-199 Unassigned */
  case 200:
    return "OK";
  case 201:
    return "Created";
  case 202:
    return "Accepted";
  case 203:
    return "Non-Authoritative Information";
  case 204:
    return "No Content";
  case 205:
    return "Reset Content";
  case 206:
    return "Partial Content";
  case 207:
    return "Multi-Status";
  case 208:
    return "Already Reported";
  /* 209-225 Unassigned */
  case 226:
    return "IM Used";
  /* 227-299 Unassigned */
  case 300:
    return "Multiple Choices";
  case 301:
    return "Moved Permanently";
  case 302:
    return "Found";
  case 303:
    return "See Other";
  case 304:
    return "Not Modified";
  case 305:
    return "Use Proxy";
  case 306:
    return "(Unused)  [";
  case 307:
    return "Temporary Redirect";
  case 308:
    return "Permanent Redirect";
  /* 309-399 Unassigned */
  case 400:
    return "Bad Request";
  case 401:
    return "Unauthorized";
  case 402:
    return "Payment Required";
  case 403:
    return "Forbidden";
  case 404:
    return "Not Found";
  case 405:
    return "Method Not Allowed";
  case 406:
    return "Not Acceptable";
  case 407:
    return "Proxy Authentication Required";
  case 408:
    return "Request Timeout";
  case 409:
    return "Conflict";
  case 410:
    return "Gone";
  case 411:
    return "Length Required";
  case 412:
    return "Precondition Failed";
  case 413:
    return "Content Too Large";
  case 414:
    return "URI Too Long";
  case 415:
    return "Unsupported Media Type";
  case 416:
    return "Range Not Satisfiable";
  case 417:
    return "Expectation Failed";
  case 418:
    return "(Unused)";
  /* 419-420 Unassigned */
  case 421:
    return "Misdirected Request";
  case 422:
    return "Unprocessable Content";
  case 423:
    return "Locked";
  case 424:
    return "Failed Dependency";
  case 425:
    return "Too Early";
  case 426:
    return "Upgrade Required";
  /* 427 Unassigned */
  case 428:
    return "Precondition Required";
  case 429:
    return "Too Many Requests";
  /* 430 Unassigned */
  case 431:
    return "Request Header Fields Too Large";
  /* 432-450 Unassigned */
  case 451:
    return "Unavailable For Legal Reasons";
  /* 452-499 Unassigned */
  case 500:
    return "Internal Server Error";
  case 501:
    return "Not Implemented";
  case 502:
    return "Bad Gateway";
  case 503:
    return "Service Unavailable";
  case 504:
    return "Gateway Timeout";
  case 505:
    return "HTTP Version Not Supported";
  case 506:
    return "Variant Also Negotiates";
  case 507:
    return "Insufficient Storage";
  case 508:
    return "Loop Detected";
  /* 509 Unassigned */
  case 510:
    return "Not Extended";
  case 511:
    return "Network Authentication Required";
  /* 512-599 Unassigned */
  default:
    return "Unassigned";
  }
};
