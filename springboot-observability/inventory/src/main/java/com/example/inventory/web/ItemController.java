package com.example.inventory.web;

import com.example.inventory.data.ItemRepository;
import com.example.inventory.domain.Item;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("items")
@RequiredArgsConstructor
@Slf4j
public class ItemController {

    private final ItemRepository itemRepository;

    @GetMapping()
    public ResponseEntity<List<Item>> getItems() {
        return ResponseEntity.ok((List<Item>) itemRepository.findAll());
    }

    @GetMapping("/{id}")
    public ResponseEntity<Item> getItem(@PathVariable Integer id) {
        log.info("Requesting item {}", id);
        return itemRepository.findById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }
}
