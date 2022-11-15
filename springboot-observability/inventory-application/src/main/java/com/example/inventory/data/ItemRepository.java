package com.example.inventory.data;

import com.example.inventory.domain.Item;
import org.springframework.data.repository.CrudRepository;

public interface ItemRepository extends CrudRepository<Item, Integer> {
}
