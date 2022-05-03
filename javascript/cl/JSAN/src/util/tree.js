class Node {
    constructor(data, parent = null) {
        this.data = data;
        this.parent = parent;
        this.children = [];
    }
}

class Tree {
    constructor(data) {
        this._root = new Node(data);
    }

    add(data, parent) {
        const child = new Node(data);
        child.parent = parent;
        parent.children.push(child);
        return child;
    }
}

export {
    Tree
}