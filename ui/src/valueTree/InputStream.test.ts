import { InputStream } from "./InputStream";
import { TextEncoder } from "util";

describe("readString", () => {
  test("read multiple strings", () => {
    const encoder = new TextEncoder();
    const stream = new InputStream(
      encoder.encode(
        "1test1" + String.fromCharCode(0) + "2test2" + String.fromCharCode(0)
      )
    );

    expect(stream.readString()).toEqual("1test1");
    expect(stream.readString()).toEqual("2test2");
    expect(stream.readString()).toEqual("");
  });
});

// Using compressedInt values written to a file in JUCE
describe("readCompressedInt", () => {
  test("1 byte", () => {
    const compressed = [0x01, 0x7b];
    const stream = new InputStream(Uint8Array.from(compressed));
    expect(stream.readCompressedInt()).toEqual(123);
  });

  test("2 bytes", () => {
    const compressed = [0x02, 0xd2, 0x04];
    const stream = new InputStream(Uint8Array.from(compressed));
    expect(stream.readCompressedInt()).toEqual(1234);
  });

  test("3 bytes", () => {
    const compressed = [0x03, 0x87, 0xd6, 0x12];
    const stream = new InputStream(Uint8Array.from(compressed));
    expect(stream.readCompressedInt()).toEqual(1234567);
  });

  test("4 bytes", () => {
    const compressed = [0x04, 0x15, 0xcd, 0x5b, 0x07];
    const stream = new InputStream(Uint8Array.from(compressed));
    expect(stream.readCompressedInt()).toEqual(123456789);
  });
});
