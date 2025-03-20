static inline bool is_httpwspace (
    char character
)
{
  /**
   * [RFC 7230](https://www.ietf.org/rfc/rfc7230.txt)
   * Section 3.2.3 - Whitespace
   *
   *   OWS            = *( SP / HTAB )
   *                  ; optional whitespace
   *   RWS            = 1*( SP / HTAB )
   *                  ; required whitespace
   *   BWS            = OWS
   *                ; "bad" whitespace
   */

  switch (character) {
  case ' ':
  case '\t':
    return true;

  default:
    return false;
  }
}
