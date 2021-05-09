export class InputStream {
  constructor(private data: string) {}

  private readPosition = 0;

  readString = (): string => {
    let buffer = "";

    while (true) {
      const c = this.readByte();

      if (c.charCodeAt(0) === 0) return buffer;

      buffer += String(c);
    }
  };

  readByte = (): string => {
    const byte = this.data[this.readPosition];
    this.incrementReadPosition(1);
    return byte;
  };

  readCompressedInt = (): number => {
    // const
  };

  private incrementReadPosition = (delta: number) => {
    this.readPosition = Math.min(
      this.readPosition + delta,
      this.data.length - 1
    );
  };

  // read = (size: number): string => {
  //   while (size > 0)
  //   {
  //       const numToRead = Math.min(size, 0x70000000);
  //       const numRead = read (juce::addBytesToPointer (destBuffer, totalRead), numToRead);
  //       jassert (numRead <= numToRead);

  //       if (numRead < 0) return (ssize_t) numRead;
  //       if (numRead == 0) break;

  //       size -= (size_t) numRead;
  //       totalRead += numRead;
  //   }
  // }
}
