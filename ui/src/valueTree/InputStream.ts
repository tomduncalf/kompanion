import { assert } from "console";

export class InputStream {
  constructor(private data: Uint8Array) {}

  private readPosition = 0;

  readString = (): string => {
    let buffer = "";

    while (true) {
      const c = this.readByte();
      if (c === 0) return buffer;

      buffer += String.fromCharCode(c);
    }
  };

  readByte = (): number => {
    const byte = this.data[this.readPosition];
    this.incrementReadPosition(1);
    return byte;
  };

  readCompressedInt = (): number => {
    const sizeByte = this.readByte();

    if (sizeByte === 0) return 0;

    const numBytes = sizeByte & 0x7f;

    if (numBytes > 4) {
      assert(false);
      return 0;
    }

    let bytes: number[] = [0, 0, 0, 0];

    // TODO error handling: if (read (bytes, numBytes) != numBytes)
    for (let i = 0; i < numBytes; i++) {
      bytes[i] = this.readByte();
    }

    // from ByteOrder::makeInt
    const number =
      bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);

    return sizeByte >> 7 ? -number : number;
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
  //       const numRead = this.read (juce::addBytesToPointer (destBuffer, totalRead), numToRead);
  //       jassert (numRead <= numToRead);

  //       if (numRead < 0) return (ssize_t) numRead;
  //       if (numRead == 0) break;

  //       size -= (size_t) numRead;
  //       totalRead += numRead;
  //   }
  // }
}
