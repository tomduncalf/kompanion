import { InputStream } from "./InputStream";

test("readString", () => {
  const stream = new InputStream(
    "1test1" + String.fromCharCode(0) + "2test2" + String.fromCharCode(0)
  );

  expect(stream.readString()).toEqual("1test1");
  expect(stream.readString()).toEqual("2test2");
  expect(stream.readString()).toEqual("");
});

test("readCompressedInt", () => {});
