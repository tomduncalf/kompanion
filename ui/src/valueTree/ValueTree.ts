/**
 * A Typescript implementation of the basics of JUCE's ValueTree class, to
 * allow us to have a synchronised read-only copy of an app's state in JS
 */

import { assert } from "console";
import { InputStream, JuceVariant } from "./InputStream";

export class ValueTree {
  constructor(
    public type: string = "",
    public properties: Map<string, JuceVariant> = new Map(),
    public children: ValueTree[] = [],
    public parent: ValueTree | undefined = undefined
  ) {}

  isValid = (): boolean => {
    return this.type !== "";
  };

  readFromStream = (input: InputStream) => {
    const newTree = ValueTree.readFromStream(input);
    this.replaceWithValueTree(newTree);
  };

  replaceWithValueTree = (tree: ValueTree) => {
    this.type = tree.type;
    this.properties = tree.properties;
    this.children = tree.children;
    this.parent = tree.parent;
  };

  static readFromStream(input: InputStream) {
    const type = input.readString();

    if (type === "") return new ValueTree();

    const tree = new ValueTree(type);
    const numProps = input.readCompressedInt();

    if (numProps < 0) {
      assert(false, "Data is corrupted");
      return tree;
    }

    for (let i = 0; i < numProps; i++) {
      const name = input.readString();

      if (name !== "") {
        tree.properties.set(name, input.readVar());
      } else {
        assert(false, "Data is corrupted");
      }
    }

    const numChildren = input.readCompressedInt();
    for (let i = 0; i < numChildren; i++) {
      const child = ValueTree.readFromStream(input);

      if (!child.isValid()) return tree;

      tree.children.push(child);
      child.parent = tree;
    }

    return tree;
  }
}
