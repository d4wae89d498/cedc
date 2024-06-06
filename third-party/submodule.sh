#!/bin/sh

# Function to move a submodule
move_submodule() {
    if test $# != 2; then
        echo "Usage: $0 move <source> <dest>"
        exit 1
    fi

    OLD_PATH=$1
    NEW_PATH=$2

    echo "Moving submodule $OLD_PATH to $NEW_PATH ..."

    git config -f .gitmodules submodule.$OLD_PATH.path $NEW_PATH
    git mv $OLD_PATH $NEW_PATH
    git config -f .git/config submodule.$OLD_PATH.path $NEW_PATH
    git add .gitmodules
    git add -A $NEW_PATH
    git commit -m "Renamed submodule directory from $OLD_PATH to $NEW_PATH"
    git submodule sync
}

# Function to delete a submodule
delete_submodule() {
    if test $# != 2; then
        echo "Usage: $0 delete <submodule_path>"
        exit 1
    fi

    SUBMODULE_PATH=$1

    echo "Deleting submodule $SUBMODULE_PATH ..."

    git submodule deinit -f -- $SUBMODULE_PATH
    git rm -f $SUBMODULE_PATH
    rm -rf .git/modules/$SUBMODULE_PATH
    rm -rf $SUBMODULE_PATH
    git config -f .gitmodules --remove-section submodule.$SUBMODULE_PATH
    git add .gitmodules
    git commit -m "Removed submodule directory $SUBMODULE_PATH"
    git submodule sync
}

# Check the action argument
if test $# -lt 1; then
    echo "Usage: $0 <move|delete> <args>"
    exit 1
fi

ACTION=$1
shift

# Execute the appropriate action
case $ACTION in
    move)
        move_submodule "$@"
        ;;
    delete)
        delete_submodule "$@"
        ;;
    *)
        echo "Invalid action: $ACTION. Use 'move' or 'delete'."
        exit 1
        ;;
esac
