/**
 * A Typescript implementation of the basics of JUCE's ValueTree class, to
 * allow us to have a synchronised read-only copy of an app's state in JS
 */

import { assert } from "console";
import { InputStream, JuceVariant } from "./InputStream";

export class ValueTree {
  constructor(
    public type: string = "",
    public properties: Record<string, JuceVariant> = {},
    public children: ValueTree[] = [],
    public parent: ValueTree | undefined = undefined
  ) {}

  isValid = (): boolean => {
    return this.type !== "";
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
        tree.properties[name] = input.readVar();
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
