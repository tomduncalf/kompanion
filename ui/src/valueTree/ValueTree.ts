/**
 * A Typescript implementation of the basics of JUCE's ValueTree class, to
 * allow us to have a synchronised read-only copy of an app's state in JS
 */

import { assert } from "console";
import { InputStream } from "./InputStream";

type PropertyType = string | number | boolean;

export class ValueTree {
  constructor(
    public type: string = "",
    public properties: Record<string, PropertyType> = {},
    public children: ValueTree[] = []
  ) {}

  isValid = (): boolean => {
    return this.type !== "";
  };

  static readFromStream(input: InputStream) {
    const type = input.readString();

    if (type === "") return new ValueTree();

    const tree = new ValueTree(type);
    const numProps = input.readCompressedInt();

    if (numProps < 0)
    {
      assert(false); // Data is corrupted
      return tree
    }

    for (let i = 0; i<numProps;i++)
    {
      const name = input.readString();

      if (name !== '')
      tree.properties[name] =
    }
  }
}
