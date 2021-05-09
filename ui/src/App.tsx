import "./App.css";
import { observer } from "mobx-react";
import { ValueTree } from "./valueTree/ValueTree";
import { useEffect } from "react";
import { InputStream } from "./valueTree/InputStream";
import { applyChange } from "./valueTree/ValueTreeSynchroniser";

const valueTree = new ValueTree();

const App = observer(() => {
  useEffect(() => {
    (async () => {
      const buffer = await (
        await fetch("/assets/valueTree/valueTreeFull.bin")
      ).arrayBuffer();

      const vt = ValueTree.readFromStream(
        new InputStream(new Uint8Array(buffer))
      );
      valueTree.replaceWithValueTree(vt);
    })();
  }, []);

  const doSomething = async () => {
    const buffer = await (
      await fetch("/assets/syncMessages/setStringProperty.bin")
    ).text();
    applyChange(valueTree, buffer);
  };

  return (
    <>
      <div className="App">{valueTree.type}</div>
      <div className="App">{valueTree.properties.get("stringProperty")}</div>
      <button onClick={doSomething}>do something</button>
    </>
  );
});

export default App;
