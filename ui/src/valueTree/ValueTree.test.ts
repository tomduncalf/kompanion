import { readFileSync } from "fs";
import { join } from "path";
import { inspect } from "util";
import { InputStream } from "./InputStream";
import { ValueTree } from "./ValueTree";

describe("readFromStream", () => {
  test("read tree successfully", () => {
    const file = readFileSync(
      join(__dirname, "..", "..", "testAssets", "valueTree")
    );
    const tree = ValueTree.readFromStream(
      new InputStream(new Uint8Array(file))
    );

    expect(tree.type).toEqual("TestTree");
    expect(tree.parent).toEqual(undefined);
    expect(tree.isValid()).toBeTruthy();

    expect(Object.keys(tree.properties)).toHaveLength(6);
    expect(tree.properties["stringProperty"]).toEqual("Test");
    expect(tree.properties["intProperty"]).toEqual(1234);
    expect(tree.properties["int64Property"]!.toString()).toEqual(
      "9223372036854775800"
    );
    expect(tree.properties["doubleProperty"]).toEqual(0.1234567);
    expect(tree.properties["boolProperty"]).toEqual(true);
    expect(tree.properties["arrayProperty"]).toEqual(["Test", 1234, true]);

    expect(tree.children).toHaveLength(2);

    expect(tree.children[0].type).toEqual("TestChild1");
    expect(tree.children[0].parent).toEqual(tree);
    expect(tree.children[0].isValid()).toBeTruthy();

    expect(Object.keys(tree.children[0].properties)).toHaveLength(1);
    expect(tree.children[0].properties["stringProperty"]).toEqual(
      "TestChildProperty"
    );

    expect(tree.children[0].children).toHaveLength(1);
    expect(tree.children[0].children[0].type).toEqual("TestNestedChild1");
    expect(tree.children[0].children[0].parent).toEqual(tree.children[0]);
    expect(tree.children[0].children[0].isValid()).toBeTruthy();

    expect(Object.keys(tree.children[0].children[0].properties)).toHaveLength(
      1
    );
    expect(tree.children[0].children[0].properties["stringProperty"]).toEqual(
      "TestNestedChildProperty"
    );

    expect(tree.children[1].type).toEqual("TestChild2");
    expect(tree.children[1].parent).toEqual(tree);
    expect(tree.children[1].isValid()).toBeTruthy();

    expect(Object.keys(tree.children[1].properties)).toHaveLength(0);
    expect(tree.children[1].children).toHaveLength(0);
  });
});
