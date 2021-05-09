/**
 * A Typescript implementation of JUCE's ValueTreeSynchroniser class, to
 * allow our JS app to receive ValueTree state updates. The implementation
 * is read-only, i.e. it can only receive updates, not send them.
 */

import { assert } from "console";
import { InputStream } from "./InputStream";
import { ValueTree } from "./ValueTree";

enum ChangeType {
  propertyChanged = 1,
  fullSync = 2,
  childAdded = 3,
  childRemoved = 4,
  childMoved = 5,
  propertyRemoved = 6,
}

export const applyChange = (valueTree: ValueTree, input: string): boolean => {
  const inputStream = new InputStream(new TextEncoder().encode(input));

  const type: ChangeType = inputStream.readByte();

  if (type === ChangeType.fullSync) {
    valueTree.readFromStream(inputStream);
    return true;
  }

  const subtree = readSubTreeLocation(valueTree, inputStream);

  if (!subtree.isValid()) return false;

  switch (type) {
    case ChangeType.propertyChanged: {
      const property = inputStream.readString();
      subtree.properties.set(property, inputStream.readVar());
      return true;
    }

    case ChangeType.propertyRemoved: {
      const property = inputStream.readString();
      subtree.properties.delete(property);
      return true;
    }

    case ChangeType.childAdded: {
      const index = inputStream.readCompressedInt();
      subtree.children.splice(index, 0, ValueTree.readFromStream(inputStream));
      return true;
    }

    case ChangeType.childRemoved: {
      const index = inputStream.readCompressedInt();
      if (index < subtree.children.length && index >= 0) {
        subtree.children.splice(index, 1);
        return true;
      }

      assert(
        false,
        "Invalid child index - data corrupt or trees are out of sync"
      );
      break;
    }

    case ChangeType.childMoved: {
      const oldIndex = inputStream.readCompressedInt();
      const newIndex = inputStream.readCompressedInt();

      if (
        oldIndex < subtree.children.length &&
        oldIndex >= 0 &&
        newIndex < subtree.children.length &&
        newIndex >= 0
      ) {
        const temp = subtree.children[oldIndex];
        subtree.children[oldIndex] = subtree.children[newIndex];
        subtree.children[newIndex] = temp;

        return true;
      }

      assert(
        false,
        "Invalid child index - data corrupt or trees are out of sync"
      );
      break;
    }

    default:
      assert(false, "Invalid operation received - data corrupt");
      break;
  }

  return false;
};

const readSubTreeLocation = (valueTree: ValueTree, input: InputStream) => {
  const numLevels = input.readCompressedInt();

  if (numLevels > 65536 || numLevels < 0) return new ValueTree();

  for (let i = numLevels; --i >= 0; ) {
    const index = input.readCompressedInt();

    if (index > valueTree.children.length || index < 0) return new ValueTree();

    valueTree = valueTree.children[index];
  }

  return valueTree;
};
